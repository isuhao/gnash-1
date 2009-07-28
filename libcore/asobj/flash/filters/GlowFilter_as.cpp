// 
//   Copyright (C) 2007, 2008, 2009 Free Software Foundation, Inc.
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


#include "as_object.h"
#include "GlowFilter.h"
#include "VM.h"
#include "Global_as.h"
#include "builtin_function.h"
#include "BitmapFilter_as.h"

namespace gnash {

class GlowFilter_as : public as_object, public GlowFilter
{
public:
    static as_value color_gs(const fn_call& fn);

    static as_value alpha_gs(const fn_call& fn);

    static as_value blurX_gs(const fn_call& fn);

    static as_value blurY_gs(const fn_call& fn);

    static as_value strength_gs(const fn_call& fn);

    static as_value quality_gs(const fn_call& fn);

    static as_value inner_gs(const fn_call& fn);

    static as_value knockout_gs(const fn_call& fn);


    static as_value bitmap_clone(const fn_call& fn);

    GlowFilter_as(as_object *obj)
        :
        as_object(obj)
    {}
    
    static as_object* Interface();
    static void attachInterface(as_object& o);
    static void attachProperties(as_object& o);
    static void registerCtor(as_object& where);
    static as_value ctor(const fn_call& fn);
private:
    static boost::intrusive_ptr<as_object> s_interface;

};


boost::intrusive_ptr<as_object> GlowFilter_as::s_interface;

as_object*
GlowFilter_as::Interface() {
    if (GlowFilter_as::s_interface == NULL) {
        GlowFilter_as::s_interface = new as_object (getBitmapFilterInterface());
        VM::get().addStatic(GlowFilter_as::s_interface.get());
        GlowFilter_as::attachInterface(*GlowFilter_as::s_interface);
    }
    return GlowFilter_as::s_interface.get();
}

void
glowfilter_class_init(as_object& where, const ObjectURI& uri)
{
    boost::intrusive_ptr<as_object> cl;
    if (cl != NULL) return;
    Global_as* gl = getGlobal(where);
    cl = gl->createClass(&GlowFilter_as::ctor, GlowFilter_as::Interface());
    VM::get().addStatic(cl.get());
    GlowFilter_as::attachInterface(*cl);
    where.init_member(getName(uri), cl.get(),
		    as_object::DefaultFlags, getNamespace(uri));
}


void
GlowFilter_as::attachInterface(as_object& o) {
    Global_as* gl = getGlobal(o);
    boost::intrusive_ptr<builtin_function> gs;
    o.set_member(VM::get().getStringTable().find("clone"), gl->createFunction(bitmap_clone));

}

void
GlowFilter_as::attachProperties(as_object& o) {
    boost::intrusive_ptr<builtin_function> gs;

    o.init_property("color" , GlowFilter_as::color_gs, 
        GlowFilter_as::color_gs);

    o.init_property("alpha" , GlowFilter_as::alpha_gs, 
        GlowFilter_as::alpha_gs);

    o.init_property("blurX" , GlowFilter_as::blurX_gs, 
        GlowFilter_as::blurX_gs);

    o.init_property("blurY" , GlowFilter_as::blurY_gs, 
        GlowFilter_as::blurY_gs);

    o.init_property("strength" , GlowFilter_as::strength_gs, 
        GlowFilter_as::strength_gs);

    o.init_property("quality" , GlowFilter_as::quality_gs, 
        GlowFilter_as::quality_gs);

    o.init_property("inner" , GlowFilter_as::inner_gs, 
        GlowFilter_as::inner_gs);

    o.init_property("knockout" , GlowFilter_as::knockout_gs, 
        GlowFilter_as::knockout_gs);

}

as_value GlowFilter_as::color_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_color );
    }
    boost::uint32_t sp_color = fn.arg(0).to_number<boost::uint32_t> ();
    ptr->m_color = sp_color;
    return as_value();
}
as_value
GlowFilter_as::alpha_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_alpha );
    }
    boost::uint8_t sp_alpha = fn.arg(0).to_number<boost::uint8_t> ();
    ptr->m_alpha = sp_alpha;
    return as_value();
}
as_value
GlowFilter_as::blurX_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_blurX );
    }
    float sp_blurX = fn.arg(0).to_number<float> ();
    ptr->m_blurX = sp_blurX;
    return as_value();
}
as_value
GlowFilter_as::blurY_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_blurY );
    }
    float sp_blurY = fn.arg(0).to_number<float> ();
    ptr->m_blurY = sp_blurY;
    return as_value();
}
as_value
GlowFilter_as::strength_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_strength );
    }
    float sp_strength = fn.arg(0).to_number<float> ();
    ptr->m_strength = sp_strength;
    return as_value();
}
as_value
GlowFilter_as::quality_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_quality );
    }
    boost::uint8_t sp_quality = fn.arg(0).to_number<boost::uint8_t> ();
    ptr->m_quality = sp_quality;
    return as_value();
}
as_value
GlowFilter_as::inner_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_inner );
    }
    bool sp_inner = fn.arg(0).to_bool ();
    ptr->m_inner = sp_inner;
    return as_value();
}
as_value
GlowFilter_as::knockout_gs(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    if (fn.nargs == 0) {
        return as_value(ptr->m_knockout );
    }
    bool sp_knockout = fn.arg(0).to_bool ();
    ptr->m_knockout = sp_knockout;
    return as_value();
 }

as_value GlowFilter_as::bitmap_clone(const fn_call& fn)
{
    boost::intrusive_ptr<GlowFilter_as> ptr = ensureType<GlowFilter_as>(fn.this_ptr);
    boost::intrusive_ptr<GlowFilter_as> obj = new GlowFilter_as(*ptr);
    boost::intrusive_ptr<as_object> r = obj;
    r->set_prototype(ptr->get_prototype());
    r->copyProperties(*ptr);
    return as_value(r);
 }

as_value
GlowFilter_as::ctor(const fn_call& )
{
    boost::intrusive_ptr<as_object> obj = new GlowFilter_as(GlowFilter_as::Interface());

    GlowFilter_as::attachProperties(*obj);


    return as_value(obj.get());

}

}
