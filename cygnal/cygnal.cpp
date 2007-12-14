// cygnal.cpp:  GNU streaming Flash media server, for Gnash.
// 
//   Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
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
// 


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <signal.h>
#include <vector>
#include <sys/mman.h>
#include <cerrno>

extern "C"{
# include <unistd.h>
#ifdef HAVE_GETOPT_H
# include <getopt.h>
#endif
#ifndef __GNUC__
 extern int optind, getopt(int, char *const *, const char *);
 extern char *optarg;
#endif
}

#include "network.h"
#include "log.h"
#include "crc.h"
#include "rtmp.h"
#include "http.h"
#include "limits.h"
#include "netstats.h"
#include "statistics.h"
#include "stream.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gettext.h"

#ifdef ENABLE_NLS
#include <locale.h>
#endif

#include <boost/date_time/gregorian/gregorian.hpp>
//#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

using gnash::log_msg;
using namespace std;
using namespace cygnal;
using namespace gnash;
using namespace amf;

static void usage(const char *proc);
static void version_and_copyright();
static void cntrlc_handler(int sig);

//static void start_thread();
static void rtmp_thread(struct thread_params *conndata);
static void http_thread(struct thread_params *conndata);
static void ssl_thread(struct thread_params *conndata);
static void stream_thread(struct thread_params *sendfile);
static void dispatch_thread(struct thread_params *params);

LogFile& dbglogfile = LogFile::getDefaultInstance();
CRcInitFile& crcfile = CRcInitFile::getDefaultInstance();

struct thread_params {
    int netfd;
    int port;
    char filespec[256];
    Statistics *statistics;
};

static struct sigaction  act;

// The next few global variables have to be global because Boost
// threads don't take arguments. Since these are set in main() before
// any of the threads are started, and it's value should never change,
// it's safe to use these without a mutex, as all threads share the
// same read-only value.

// This is the default path to look in for files to be streamed.
const char *docroot;

// This is the number of times a thread loop continues, for debugging only
int thread_retries = 10;

// This is added to the default ports for testing so it doesn't
// conflict with apache on the same machine.
static int port_offset = 0;

// end of globals


int
main(int argc, char *argv[])
{
    // Initialize national language support
#ifdef ENABLE_NLS
    setlocale (LC_MESSAGES, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
#endif
    // scan for the two main long GNU options
    int c;
    for (c=0; c<argc; c++) {
        if (strcmp("--help", argv[c]) == 0) {
            version_and_copyright();
            printf("\n");
            usage(argv[0]);
            exit(0);
        }

        if (strcmp("--version", argv[c]) == 0) {
            version_and_copyright();
            exit(0);
        }
    }

    crcfile.loadFiles();

    if (crcfile.getDebugLog().size()) {
	dbglogfile.openLog(crcfile.getDebugLog());
    } else {
	dbglogfile.openLog("/tmp/cygnal-dbg.log");
    }
    
    if (crcfile.verbosityLevel() > 0) {
        dbglogfile.setVerbosity(crcfile.verbosityLevel());
    }    
    
    if (crcfile.getDocumentRoot().size() > 0) {
	docroot = crcfile.getDocumentRoot().c_str();
	log_msg (_("Document Root for media files is: %s"),
		   docroot);
    } else {
	docroot = "/var/www/html/software/gnash/tests/";
    }
    
    while ((c = getopt (argc, argv, "hvp:d")) != -1) {
	switch (c) {
	  case 'h':
	      usage (argv[0]);
              exit(0);
	  case 'v':
              dbglogfile.setVerbosity();
	      log_msg (_("Verbose output turned on"));
	      break;
	  case 'p':
	      port_offset = strtol(optarg, NULL, 0);
	      crcfile.setPortOffset(port_offset);
	      break;
	  case 'd':
	      crcfile.dump();
	      exit(0);
	      break;
        }
    }
    

    // get the file name from the command line
    while (optind < argc) {
        log_error (_("Extraneous argument: %s"), argv[optind]);
    }
    
    // Trap ^C (SIGINT) so we can kill all the threads
    act.sa_handler = cntrlc_handler;
    sigaction (SIGINT, &act, NULL);

    struct thread_params rtmp_data;
    struct thread_params http_data;
    struct thread_params ssl_data;
    rtmp_data.port = port_offset + 1935;
//    boost::thread rtmp_port(boost::bind(&rtmp_thread, &rtmp_data));

    http_data.port = port_offset + 80;
    Statistics st;
    http_data.statistics = &st;
    boost::thread http_port(boost::bind(&http_thread, &http_data));

    ssl_data.port = port_offset + 443;
//    boost::thread ssl_port(boost::bind(&ssl_thread, &ssl_data));
    
//    boost::thread rtmp_port(&rtmp_thread);
//    boost::thread http_port(&http_thread);
//    boost::thread ssl_port(&ssl_thread);

    // wait for the thread to finish
//    rtmp_port.join();
    http_port.join();
//    ssl_port.join();

    log_msg (_("All done I think..."));
    
    return(0);
}

static void
http_thread(struct thread_params *conndata)
{
    GNASH_REPORT_FUNCTION;
    int retries = 0;
    HTTP www;
//    struct thread_params thread_data;
    string url, filespec, parameters;
    string::size_type pos;
    int port = RTMPT + port_offset;
    int filesize;
    struct stat filestats;

    www.toggleDebug(true);
    
    www.createServer(port);
    while (retries++ < thread_retries) {
	log_msg(_("%s: Thread for port %d looping..."), __PRETTY_FUNCTION__, port);
	www.newConnection(true);

	conndata->statistics->setFileType(NetStats::RTMPT);
	conndata->statistics->startClock();
	conndata->netfd = www.getFileFd();
	url = docroot;
	url += www.waitForGetRequest();
	pos = url.find("?");
	filespec = url.substr(0, pos);
	parameters = url.substr(pos + 1, url.size());
	// Get the file size for the HTTP header
	
	if (www.getFileStats(filespec) == HTTP::ERROR) {
	    www.formatErrorResponse(HTTP::NOT_FOUND);
	}
	www.sendGetReply(HTTP::LIFE_IS_GOOD);
//	strcpy(thread_data.filespec, filespec.c_str());
//	thread_data.statistics = conndata->statistics;
	
	// Keep track of the network statistics
	conndata->statistics->stopClock();
// 	log_msg (_("Bytes read: %d"), www.getBytesIn());
// 	log_msg (_("Bytes written: %d"), www.getBytesOut());
//	st.setBytes(www.getBytesIn() + www.getBytesOut());
	conndata->statistics->addStats();
//	www.resetBytesIn();
//	www.resetBytesOut();
	
	if (url != docroot) {
	    log_msg (_("File to load is: %s"), filespec.c_str());
	    log_msg (_("Parameters are: %s"), parameters.c_str());
	    memset(conndata->filespec, 0, 256);
	    memcpy(conndata->filespec, filespec.c_str(), filespec.size());
	    boost::thread sendthr(boost::bind(&stream_thread, conndata));
	    sendthr.join();
	}
	// See if this is a persistant connection
// 	if (!www.keepAlive()) {
// 	    www.closeConnection();
// 	}
	conndata->statistics->dump();
    }
}

static void
rtmp_thread(struct thread_params *conndata)
{
    GNASH_REPORT_FUNCTION;
    int retries = 0;
    RTMPproto proto;
    
    Statistics st;
    st.setFileType(NetStats::RTMP);

    log_msg("Param port is: %d", conndata->port);
    
    proto.createServer(RTMP);
    while (retries++ < thread_retries) {
	log_msg(_("%s: Thread for RTMP port looping..."), __PRETTY_FUNCTION__);
	proto.newConnection(true);
	st.startClock();
	proto.handShakeWait();
	proto.handShakeResponse();
	proto.serverFinish();
	
	// Keep track of the network statistics
	st.stopClock();
 	log_msg (_("Bytes read: %d"), proto.getBytesIn());
 	log_msg (_("Bytes written: %d"), proto.getBytesOut());
	st.setBytes(proto.getBytesIn() + proto.getBytesOut());
	st.addStats();
	proto.resetBytesIn();
	proto.resetBytesOut();	

	st.dump();
    }    
}

static void
ssl_thread(struct thread_params *conndata)
{
    GNASH_REPORT_FUNCTION;
    int retries = 0;
    HTTP www;
    RTMPproto proto;
    struct thread_params loadfile;
    string filespec;
    int port = RTMPTS + port_offset;

    Statistics st;
    st.setFileType(NetStats::RTMPTS);    
    
    www.createServer(port);
    
    log_msg("Param port is: %d", conndata->port);
    while (retries++ < thread_retries) {
	log_msg (_("%s: Thread for port %d looping..."), __PRETTY_FUNCTION__, port);
	www.newConnection(true);
	loadfile.netfd = www.getFileFd();
	strcpy(loadfile.filespec, "Hello World");
	boost::thread sendthr(boost::bind(&stream_thread, &loadfile));
	sendthr.join();
    }
}

static void
stream_thread(struct  thread_params *params)
{
    GNASH_REPORT_FUNCTION;
    
    //struct stat stats;
    //struct thread_params loadfile;
    
    log_msg ("%s: %s", __PRETTY_FUNCTION__, params->filespec);
    
    Stream str;
    str.open(params->filespec, params->netfd, params->statistics);
    str.play();
//    ::close(params->netfd);
}


// Trap Control-C so we can cleanly exit
static void
cntrlc_handler (int /*sig*/)
{
    log_msg(_("Got an interrupt"));

    exit(-1);
}

static void
version_and_copyright()
{
    printf (_(
"Cygnal %s\n"
"Copyright (C) 2006, 2007 Free Software Foundation, Inc.\n"
"Cygnal comes with NO WARRANTY, to the extent permitted by law.\n"
"You may redistribute copies of Cygnal under the terms of the GNU General\n"
"Public License.  For more information, see the file named COPYING.\n"),
        VERSION);
}

static void
usage(const char* /*proc*/)
{
    printf(_(
	"cygnal -- an streaming media server.\n"
	"\n"
	"usage: cygnal [options...]\n"
	"  --help(-h)  Print this info.\n"
	"  --version   Print the version numbers.\n"
	"  --verbose (-v)   Output verbose debug info.\n"
	"  --port-offset (-p)   RTMPT port offset.\n"
	));
}

//} // end of cygnal namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
