// Timer_as.cpp:  ActionScript "Timer" class, for Gnash.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
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
#include "gnashconfig.h"
#endif

#include "utils/Timer_as.h"
#include "log.h"
#include "fn_call.h"
#include "Global_as.h"
#include "smart_ptr.h" // for boost intrusive_ptr
#include "builtin_function.h" // need builtin_function
#include "GnashException.h" // for ActionException

namespace gnash {

// Forward declarations
namespace {
    as_value timer_start(const fn_call& fn);
    as_value timer_stop(const fn_call& fn);
    as_value timer_timer(const fn_call& fn);
    as_value timer_timerComplete(const fn_call& fn);
    as_value timer_ctor(const fn_call& fn);
    void attachTimerInterface(as_object& o);
    void attachTimerStaticInterface(as_object& o);
    as_object* getTimerInterface();

}

class Timer_as : public as_object
{

public:

    Timer_as()
        :
        as_object(getTimerInterface())
    {}
};

// extern (used by Global.cpp)
void timer_class_init(as_object& global)
{
    static boost::intrusive_ptr<as_object> cl;

    if (!cl) {
        Global_as* gl = getGlobal(global);
        cl = gl->createClass(&timer_ctor, getTimerInterface());;
        attachTimerStaticInterface(*cl);
    }

    // Register _global.Timer
    global.init_member("Timer", cl.get());
}

namespace {

void
attachTimerInterface(as_object& o)
{
    Global_as* gl = getGlobal(o);
    o.init_member("start", gl->createFunction(timer_start));
    o.init_member("stop", gl->createFunction(timer_stop));
    o.init_member("timer", gl->createFunction(timer_timer));
    o.init_member("timerComplete", gl->createFunction(timer_timerComplete));
}

void
attachTimerStaticInterface(as_object& o)
{
    Global_as* gl = getGlobal(o);

}

as_object*
getTimerInterface()
{
    static boost::intrusive_ptr<as_object> o;
    if ( ! o ) {
        o = new as_object();
        attachTimerInterface(*o);
    }
    return o.get();
}

as_value
timer_start(const fn_call& fn)
{
    boost::intrusive_ptr<Timer_as> ptr =
        ensureType<Timer_as>(fn.this_ptr);
    UNUSED(ptr);
    log_unimpl (__FUNCTION__);
    return as_value();
}

as_value
timer_stop(const fn_call& fn)
{
    boost::intrusive_ptr<Timer_as> ptr =
        ensureType<Timer_as>(fn.this_ptr);
    UNUSED(ptr);
    log_unimpl (__FUNCTION__);
    return as_value();
}

as_value
timer_timer(const fn_call& fn)
{
    boost::intrusive_ptr<Timer_as> ptr =
        ensureType<Timer_as>(fn.this_ptr);
    UNUSED(ptr);
    log_unimpl (__FUNCTION__);
    return as_value();
}

as_value
timer_timerComplete(const fn_call& fn)
{
    boost::intrusive_ptr<Timer_as> ptr =
        ensureType<Timer_as>(fn.this_ptr);
    UNUSED(ptr);
    log_unimpl (__FUNCTION__);
    return as_value();
}

as_value
timer_ctor(const fn_call& fn)
{
    boost::intrusive_ptr<as_object> obj = new Timer_as;

    return as_value(obj.get()); // will keep alive
}

} // anonymous namespace 
} // gnash namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

