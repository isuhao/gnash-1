// AudioDecoderGst.cpp: Audio decoding using Gstreamer.
// 
//   Copyright (C) 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif


#include "AudioDecoderGst.h"
#include "MediaParser.h"
#include "MediaParserGst.h"

namespace gnash {
namespace media {



AudioDecoderGst::AudioDecoderGst(SoundInfo& info)
{
    // init GStreamer. TODO: what about doing this in MediaHandlerGst ctor?
    gst_init (NULL, NULL);

    GstCaps* srccaps = gst_caps_new_simple ("audio/mpeg",
		"mpegversion", G_TYPE_INT, 1,
		"layer", G_TYPE_INT, 3,
		"rate", G_TYPE_INT, info.getSampleRate(),
		"channels", G_TYPE_INT, info.isStereo() ? 2 : 1, NULL);

    setup(srccaps);

    // FIXME: should we handle other types?
}

AudioDecoderGst::AudioDecoderGst(AudioInfo& info)
{
    // init GStreamer. TODO: what about doing this in MediaHandlerGst ctor?
    gst_init (NULL, NULL);

    GstCaps* srccaps=0;

    if (info.type == FLASH && info.codec == AUDIO_CODEC_MP3)
    {
        srccaps = gst_caps_new_simple ("audio/mpeg",
		"mpegversion", G_TYPE_INT, 1,
		"layer", G_TYPE_INT, 3,
		"rate", G_TYPE_INT, info.sampleRate,
		"channels", G_TYPE_INT, info.stereo ? 2 : 1, NULL);
        setup(srccaps);
        return;
    }
    
    if (info.type == FLASH && info.codec == AUDIO_CODEC_NELLYMOSER)
    {
        srccaps = gst_caps_new_simple ("audio/x-nellymoser",
		"rate", G_TYPE_INT, info.sampleRate,
		"channels", G_TYPE_INT, info.stereo ? 2 : 1, NULL);
        setup(srccaps);
        return;
    }

    if (info.type == FLASH) {
        throw MediaException("AudioDecoderGst: cannot handle this codec!");
    }

    ExtraInfoGst* extraaudioinfo = dynamic_cast<ExtraInfoGst*>(info.extra.get());

    if (!extraaudioinfo) {
        throw MediaException("AudioDecoderGst: cannot handle this codec!");
    }

    setup(extraaudioinfo->caps);
}

AudioDecoderGst::~AudioDecoderGst()
{
    assert(g_queue_is_empty (_decoder.queue));
    swfdec_gst_decoder_push_eos(&_decoder);
    swfdec_gst_decoder_finish(&_decoder);
}



void AudioDecoderGst::setup(GstCaps* srccaps)
{
    if (!srccaps) {
        throw MediaException(_("AudioDecoderGst: internal error (caps creation failed)"));      
    }

    GstCaps* sinkcaps = gst_caps_from_string ("audio/x-raw-int, endianness=byte_order, signed=(boolean)true, width=16, depth=16, rate=44100, channels=2");
    if (!sinkcaps) {
        throw MediaException(_("AudioDecoderGst: internal error (caps creation failed)"));      
    }

    // TODO: we may want to prefer other modules over audioresample, like ffaudioresample, if they are
    // available.

    bool rv = swfdec_gst_decoder_init (&_decoder, srccaps, sinkcaps, "audioconvert", "ffaudioresample", NULL);
    if (!rv) {
        throw MediaException(_("AudioDecoderGst: initialisation failed."));      
    }

    gst_caps_unref (srccaps);
    gst_caps_unref (sinkcaps);
}

void
buf_add(gpointer buf, gpointer data)
{
    boost::uint32_t* total = (boost::uint32_t*) data;

    GstBuffer* buffer = (GstBuffer*) buf;
    *total += GST_BUFFER_SIZE(buffer);
}


boost::uint8_t* 
AudioDecoderGst::pullBuffers(boost::uint32_t&  outputSize)
{
    outputSize = 0;
    
    g_queue_foreach(_decoder.queue, buf_add, &outputSize);
  
    if (!outputSize) {
        log_debug(_("Pushed data, but there's nothing to pull (yet)"));
        return 0;   
    }
    
    boost::uint8_t* rbuf = new boost::uint8_t[outputSize];
    
    boost::uint8_t* ptr = rbuf;
    
    while (true) {
    
        GstBuffer* buffer = swfdec_gst_decoder_pull (&_decoder);
        if (!buffer) {
            break;
        }
    
        memcpy(ptr, GST_BUFFER_DATA(buffer), GST_BUFFER_SIZE(buffer));
        ptr += GST_BUFFER_SIZE(buffer);
      
        gst_buffer_unref (buffer);
    }

    return rbuf;    
}

boost::uint8_t*
AudioDecoderGst::decode(boost::uint8_t* input, boost::uint32_t inputSize,
                        boost::uint32_t& outputSize,
                        boost::uint32_t& decodedData, bool /*parse*/)
{
    outputSize = decodedData = 0;

    GstBuffer* gstbuf = gst_buffer_new_and_alloc(inputSize);
    memcpy (GST_BUFFER_DATA (gstbuf), input, inputSize);

    bool success = swfdec_gst_decoder_push(&_decoder, gstbuf);
    if (!success) {
        log_error(_("AudioDecoderGst: buffer push failed."));
        gst_buffer_unref(gstbuf);
        return 0;
    }

    decodedData = inputSize;

    return pullBuffers(outputSize);
}

boost::uint8_t*
AudioDecoderGst::decode(const EncodedAudioFrame& ef, boost::uint32_t& outputSize)
{
    outputSize = 0;
    
    GstBuffer* gstbuf;
    
    EncodedExtraGstData* extradata = dynamic_cast<EncodedExtraGstData*>(ef.extradata.get());
    
    if (extradata) {
        gstbuf = extradata->buffer;
    } else {

        gstbuf = gst_buffer_new_and_alloc(ef.dataSize);
        memcpy (GST_BUFFER_DATA (gstbuf), ef.data.get(), ef.dataSize);
    }

    bool success = swfdec_gst_decoder_push(&_decoder, gstbuf);
    if (!success) {
        log_error(_("AudioDecoderGst: buffer push failed."));
        return 0;
    }

    return pullBuffers(outputSize);
}


} // end of media namespace
} // end of gnash namespace


