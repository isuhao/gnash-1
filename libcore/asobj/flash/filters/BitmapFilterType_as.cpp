// BitmapFilterType_as.cpp:  ActionScript "BitmapFilterType" class, for Gnash.
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

#include "filters/BitmapFilterType_as.h"
#include "log.h"
#include "fn_call.h"
#include "Global_as.h"
#include "Object.h"
#include "smart_ptr.h" // for boost intrusive_ptr
#include "builtin_function.h" // need builtin_function
#include "GnashException.h" // for ActionException

namespace gnash {

// Forward declarations
namespace {
    void attachBitmapFilterTypeStaticInterface(as_object& o);
}

// extern (used by Global.cpp)
void
bitmapfiltertype_class_init(as_object& where, const ObjectURI& uri)
{
    boost::intrusive_ptr<as_object> cl = new as_object(getObjectInterface());
    attachBitmapFilterTypeStaticInterface(*cl);
    where.init_member(getName(uri), cl.get(), as_object::DefaultFlags,
            getNamespace(uri));
}

namespace {

void
attachBitmapFilterTypeStaticInterface(as_object& /*o*/)
{
    // TODO: attach constants.
}

} // anonymous namespace 
} // gnash namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

