// 
//   Copyright (C) 2005, 2006 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License

// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef _CHECK_AS_
#define _CHECK_AS_

// Define USE_XTRACE to use "visual" trace
#ifdef USE_XTRACE
# include "xtrace.as"
# define trace xtrace
#endif


//
// Use check(<expression>)
// Make sure your expression doesn't contain single quotes
//
#define check(expr)  \
	if ( expr ) trace("PASSED: " + #expr + \
		" [" + __FILE__ + ":" + __LINE__ + "]" ); \
	else trace("FAILED: " + #expr + \
		" [" + __FILE__ + ":" + __LINE__ + "]" ); \

#endif // _CHECK_AS_
