// 
//     Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 
//
//

#include "Timers.h"
#include "log.h"
#include "fn_call.h"
#include "VM.h"
#include "movie_root.h"
#include "action.h" // call_method

#include <limits> // for numeric_limits
#include <functional>
#include <algorithm>

namespace gnash {

Timer::Timer()
    :
    _interval(0),
    _start(std::numeric_limits<unsigned long>::max()),
    _object(0),
    _runOnce(false)
{
}

Timer::~Timer()
{
}

void
Timer::setInterval(as_function& method, unsigned long ms,
        boost::intrusive_ptr<as_object> this_ptr, 
        ArgsContainer& args, bool runOnce)
{
    _function = &method;
    _interval = ms; 
    _object = this_ptr;
    _args = args;
    _runOnce = runOnce;
    start();
}

void
Timer::setInterval(as_function& method, unsigned long ms,
        boost::intrusive_ptr<as_object> this_ptr, bool runOnce)
{
    _function = &method;
    _interval = ms; 
    _object = this_ptr;
    _runOnce = runOnce;
    start();
}

void
Timer::setInterval(boost::intrusive_ptr<as_object> this_ptr,
        const std::string& methodName, unsigned long ms, 
        std::vector<as_value>& args, bool runOnce)
{
    _object = this_ptr;
    _methodName = methodName;
    _interval = ms; 
    _args = args;
    _runOnce = runOnce;
    start();
}

void
Timer::clearInterval()
{
    _interval = 0;
    _start = std::numeric_limits<unsigned long>::max();
}

void
Timer::start()
{
    _start = _object->getVM().getTime();
}
    

bool
Timer::expired(unsigned long now, unsigned long& elapsed)
{
    if (cleared()) return false;
    long unsigned expTime = _start + _interval;
    if (now < expTime) return false;
    elapsed = expTime-now;
    return true;
}

void
Timer::executeAndReset()
{
    if (cleared()) return;
    execute();
    if (_runOnce) clearInterval();
    else _start += _interval; // reset the timer
}

void
Timer::execute()
{

    as_value timer_method;

    as_object* super = _object->get_super(_function ? 0 : _methodName.c_str());
    VM& vm = _object->getVM();

    if (_function.get() ) {
        timer_method.set_as_function(_function.get());
    }
    else {
        string_table::key k = vm.getStringTable().find(_methodName);
        as_value tmp;

        if ( ! _object->get_member(k, &tmp) ) {
            IF_VERBOSE_ASCODING_ERRORS(
            log_aserror("object %p has no member named %s (interval method)",
                     _object, _methodName);
            );
            return;
        }

        as_function* f = tmp.to_as_function();

        if (!f) {
            IF_VERBOSE_ASCODING_ERRORS(
            log_aserror("member %s of object %p (interval method) is not "
                "a function (%s)", _methodName, (void*)_object.get(), tmp);
            );
            return;
        }
        timer_method.set_as_function(f);
    }

    as_environment env(vm); 

    // Copy args 
    std::auto_ptr<std::vector<as_value> > args(
            new std::vector<as_value>(_args));

    call_method(timer_method, &env, _object.get(), args, super);

}

#ifdef GNASH_USE_GC
void
Timer::markReachableResources() const
{
    std::for_each(_args.begin(), _args.end(),
                    std::mem_fun_ref(&as_value::setReachable));

    if (_function) _function->setReachable();
    if (_object) _object->setReachable();
}
#endif // GNASH_USE_GC

} // namespace gnash
