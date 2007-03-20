// 
//   Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "as_value.h"
#include "as_object.h"
#include "as_function.h" // for as_function
#include "sprite_instance.h" // for MOVIECLIP values
#include "as_environment.h" // for MOVIECLIP values
#include "VM.h" // for MOVIECLIP values
#include "movie_root.h" // for MOVIECLIP values
#include "gstring.h" // for automatic as_value::STRING => String as object
#include "Number.h" // for automatic as_value::NUMBER => Number as object
#include "action.h" // for call_method0

#include <cmath>	// for NAN
#include <boost/algorithm/string/case_conv.hpp>

using namespace std;

#ifdef WIN32
#	define snprintf _snprintf
#endif

namespace gnash {

#ifndef NAN
//	If this makes your compiler die with div by zero,
//	use "static double zzzero = 0.0;" and "(zzzero/zzzero)"
#	define NAN std::numeric_limits<double>::quiet_NaN();
#endif

//
// as_value -- ActionScript value type
//

static void
lowercase_if_needed(std::string& str)
{
	VM& vm = VM::get();
	if ( vm.getSWFVersion() >= 7 ) return;
	boost::to_lower(str, vm.getLocale());
}

as_value::as_value(as_function* func)
    :
    m_type(AS_FUNCTION),
    m_object_value(func)
{
    if (m_object_value) {
	m_object_value->add_ref();
    } else {
        m_type = NULLTYPE;
    }
}


// Conversion to string.
const char
*as_value::to_string(as_environment* env) const
{
    return to_tu_string(env).c_str();
}


std::string
as_value::to_std_string(as_environment* env) const
{
    const char* c = to_string(env);
    assert(c);
    return std::string(c);
}

const tu_stringi
&as_value::to_tu_stringi(as_environment* env) const
{
    return reinterpret_cast<const tu_stringi&>(to_tu_string(env));
}

// Conversion to const tu_string&.
const tu_string&
as_value::to_tu_string(as_environment* env) const
{
	switch (m_type)
	{

		case STRING:
		case MOVIECLIP:
			/* don't need to do anything */
			break;

		case NUMBER:
			// @@ Moock says if value is a NAN,
			// then result is "NaN"
			// INF goes to "Infinity"
			// -INF goes to "-Infinity"
			if (isnan(m_number_value))
			{
				m_string_value = "NaN";
			}
			else if (isinf(m_number_value))
			{
				if (m_number_value > 0.0)
				{
					m_string_value = "Infinity";
				}
				else
				{
					m_string_value = "-Infinity";
				}
			}
			else if ( m_number_value == -0.0 || m_number_value == 0.0 )
			{
					m_string_value = "0";
			}
			else
			{
				char buffer[50];
				snprintf(buffer, 50, "%.14g", m_number_value);
				m_string_value = buffer;
			}
			break;

		case UNDEFINED: 

			// Behavior depends on file version.  In
			// version 7+, it's "undefined", in versions
			// 6-, it's "".
			//
			// We'll go with the v7 behavior by default,
			// and conditionalize via _versioned()
			// functions.
			m_string_value = "undefined";

			break;

		case NULLTYPE:
			m_string_value = "null";
			break;

		case BOOLEAN:
			m_string_value = this->m_boolean_value ? "true" : "false";
			break;

		case OBJECT:
		case AS_FUNCTION:
		{
			//printf("as_value to string conversion, env=%p\n", env);
			// @@ Moock says, "the value that results from
			// calling toString() on the object".
			//
			// When the toString() method doesn't exist, or
			// doesn't return a valid number, the default
			// text representation for that object is used
			// instead.
			//
			as_object* obj = m_object_value; 
			bool gotValidToStringResult = false;
			if ( env )
			{
				std::string methodname = "toString";
				lowercase_if_needed(methodname);
				as_value method;
				if ( obj->get_member(methodname, &method) )
				{
					as_value ret = call_method0(method, env, obj);
					if ( ret.is_string() )
					{
						gotValidToStringResult=true;
						m_string_value = ret.m_string_value;
					}
					else
					{
						log_msg("call_method0(%s) did not return a string", methodname.c_str());
					}
				}
				else
				{
					log_msg("get_member(%s) returned false", methodname.c_str());
				}
			}
			if ( ! gotValidToStringResult )
			{
				if ( m_type == OBJECT )
				{
					m_string_value = "[type Object]";
				}
				else
				{
					assert(m_type == AS_FUNCTION);
					m_string_value = "[type Function]";
				}
			}
			break;
		}

		default:
			m_string_value = "<bad type> "+m_type;
			assert(0);
    }
    
    return m_string_value;
}

// Conversion to const tu_string&.
const tu_string
&as_value::to_tu_string_versioned(int version, as_environment* env) const
{
    if (m_type == UNDEFINED) {
	// Version-dependent behavior.
	if (version <= 6) {
	    m_string_value = "";
	} else {
	    m_string_value = "undefined";
	}
	return m_string_value;
    }
		
    return to_tu_string(env);
}

// Version-based Conversion to std::string
std::string
as_value::to_std_string_versioned(int version, as_environment* env) const
{
	return std::string(to_tu_string_versioned(version, env).c_str());
}

// Conversion to primitive value.
as_value
as_value::to_primitive() const
{
	switch (m_type)
	{
		case OBJECT:
		case AS_FUNCTION:
			return m_object_value->get_primitive_value();
		case UNDEFINED:
		case NULLTYPE:
		case BOOLEAN:
		case STRING:
		case NUMBER:
		default:
			return *this;
	}

}

// Conversion to double.
double
as_value::to_number(as_environment* env) const
{
	// TODO:  split in to_number_# (version based)

	int swfversion = VM::get().getSWFVersion();

	switch (m_type)
	{
		case STRING:
		{
			// @@ Moock says the rule here is: if the
			// string is a valid float literal, then it
			// gets converted; otherwise it is set to NaN.
			//
			// Also, "Infinity", "-Infinity", and "NaN"
			// are recognized by strtod() but not by Flash Player.
			char* tail=0;
			m_number_value = strtod(m_string_value.c_str(), &tail);
			if ( tail == m_string_value.c_str() || *tail != 0 )
			{
				// Failed conversion to Number.
				m_number_value = NAN;
			}
			return m_number_value;
		}

		case NULLTYPE:
		case UNDEFINED:
			// Evan: from my tests
			// Martin: I tried var foo = new Number(null) and got NaN
			if ( swfversion >= 7 ) return std::numeric_limits<double>::quiet_NaN();
			else return 0;

		case BOOLEAN:
			// Evan: from my tests
			// Martin: confirmed
			return (this->m_boolean_value) ? 1 : 0;

		case NUMBER:
			return m_number_value;

		case OBJECT:
		case AS_FUNCTION:
		{
			// @@ Moock says the result here should be
			// "the return value of the object's valueOf()
			// method".
			//
			// Arrays and Movieclips should return NaN.

			//log_msg("OBJECT to number conversion, env is %p", env);

			as_object* obj = m_object_value; 
			bool gotValidValueOfResult = false;
			if ( env )
			{
				std::string methodname = "valueOf";
				lowercase_if_needed(methodname);
				as_value method;
				if ( obj->get_member(methodname, &method) )
				{
					as_value ret = call_method0(method, env, obj);
					if ( ret.is_number() )
					{
						gotValidValueOfResult=true;
						return ret.m_number_value;
					}
					else
					{
						log_msg("call_method0(%s) did not return a number", methodname.c_str());
					}
				}
				else
				{
					log_msg("get_member(%s) returned false", methodname.c_str());
				}
			}
			if ( ! gotValidValueOfResult )
			{
				return obj->get_numeric_value(); 
			}
		}

		case MOVIECLIP:
			// This is tested, no valueOf is going
			// to be invoked for movieclips.
			return NAN; 

		default:
			// Other object types should return NaN, but if we implement that,
			// every GUI's movie canvas shrinks to size 0x0. No idea why.
			return NAN; // 0.0;
	}
}

// Conversion to boolean for SWF7 and up
bool
as_value::to_bool_v7() const
{
	    switch (m_type)
	    {
		case  STRING:
			return m_string_value != "";
		case NUMBER:
			return m_number_value && ! isnan(m_number_value);
		case BOOLEAN:
			return this->m_boolean_value;
		case OBJECT:
		case AS_FUNCTION:
			// it is possible we'll need to convert to number anyway first
			return m_object_value != NULL;
		case MOVIECLIP:
			return true;
		default:
			assert(m_type == UNDEFINED || m_type == NULLTYPE);
			return false;
	}
}

// Conversion to boolean up to SWF5
bool
as_value::to_bool_v5() const
{
	    switch (m_type)
	    {
		case  STRING:
		{
			if (m_string_value == "false") return false;
			else if (m_string_value == "true") return true;
			else
			{
				double num = to_number();
				bool ret = num && ! isnan(num);
				log_msg("m_string_value: %s, to_number: %g, to_bool: %d", m_string_value.c_str(), num, ret);
				return ret;
			}
		}
		case NUMBER:
			return ! isnan(m_number_value) && m_number_value; 
		case BOOLEAN:
			return this->m_boolean_value;
		case OBJECT:
		case AS_FUNCTION:
			// it is possible we'll need to convert to number anyway first
			return m_object_value != NULL;
		case MOVIECLIP:
			return true;
		default:
			assert(m_type == UNDEFINED || m_type == NULLTYPE);
			return false;
	}
}

// Conversion to boolean for SWF6
bool
as_value::to_bool_v6() const
{
	    switch (m_type)
	    {
		case  STRING:
		{
			if (m_string_value == "false") return false;
			else if (m_string_value == "true") return true;
			else
			{
				double num = to_number();
				bool ret = num && ! isnan(num);
				log_msg("m_string_value: %s, to_number: %g, to_bool: %d", m_string_value.c_str(), num, ret);
				return ret;
			}
		}
		case NUMBER:
			return isfinite(m_number_value) && m_number_value; 
		case BOOLEAN:
			return this->m_boolean_value;
		case OBJECT:
		case AS_FUNCTION:
			// it is possible we'll need to convert to number anyway first
			return m_object_value != NULL;
		case MOVIECLIP:
			return true;
		default:
			assert(m_type == UNDEFINED || m_type == NULLTYPE);
			return false;
	}
}

// Conversion to boolean.
bool
as_value::to_bool() const
{
    int ver = VM::get().getSWFVersion();
    if ( ver >= 7 ) return to_bool_v7();
    else if ( ver == 6 ) return to_bool_v6();
    else return to_bool_v5();
}
	
// Return value as an object.
as_object*
as_value::to_object() const
{
	switch (m_type)
	{
		case OBJECT:
		case AS_FUNCTION:
			return m_object_value;

		case MOVIECLIP:
			return to_sprite();

		case STRING:
			return init_string_instance(m_string_value.c_str()).release();

		case NUMBER:
			return init_number_instance(m_number_value).release();

		default:
			return NULL;
	}
}

sprite_instance*
as_value::to_sprite() const
{
	// Evaluate target everytime an attempt is made 
	// to fetch a movieclip value.
	sprite_instance* root = VM::get().getRoot().get_root_movie();
	as_environment& env = root->get_environment();
	// TODO: simplify next statement when m_string_value will become a std::string
	character* target = env.find_target(std::string(m_string_value.c_str()));
	if ( ! target )
	{
		log_warning("MovieClip value is a dangling reference: "
				"target '%s' not found (should set to NULL?)",
				m_string_value.c_str());
		return NULL;
	}
	else
	{
		return target->to_movie();
	}
}

void
as_value::set_sprite(const sprite_instance& sprite)
{
	drop_refs();
	m_type = MOVIECLIP;
	// TODO: simplify next statement when m_string_value will become a std::string
	m_string_value = sprite.get_text_value();
}

void
as_value::set_sprite(const std::string& path)
{
	drop_refs();
	m_type = MOVIECLIP;
	// TODO: simplify next statement when m_string_value will become a std::string
	m_string_value = path.c_str();
}

// Return value as an ActionScript function.  Returns NULL if value is
// not an ActionScript function.
as_function*
as_value::to_as_function() const
{
    if (m_type == AS_FUNCTION) {
	// OK.
	return m_object_value->to_function();
    } else {
	return NULL;
    }
}

// Force type to number.
void
as_value::convert_to_number()
{
    set_double(to_number());
}

// Force type to string.
void
as_value::convert_to_string()
{
    to_tu_string();	// init our string data.
    m_type = STRING;	// force type.
}


void
as_value::convert_to_string_versioned(int version, as_environment* env)
    // Force type to string.
{
    to_tu_string_versioned(version, env); // init our string data.
    m_type = STRING;	// force type.
}


void
as_value::set_as_object(as_object* obj)
{
	if ( ! obj )
	{
		set_null();
		return;
	}
	sprite_instance* sp = obj->to_movie();
	if ( sp )
	{
		set_sprite(*sp);
		return;
	}
	as_function* func = obj->to_function();
	if ( func )
	{
		set_as_function(func);
		return;
	}
	if (m_type != OBJECT || m_object_value != obj)
	{
		drop_refs();
		m_type = OBJECT;
		m_object_value = obj;
		if (m_object_value)
		{
			m_object_value->add_ref();
		}
	}
}

void
as_value::set_as_function(as_function* func)
{
    if (m_type != AS_FUNCTION || m_object_value != func) {
	drop_refs();
	m_type = AS_FUNCTION;
	m_object_value = func;
	if (m_object_value) {
	    m_object_value->add_ref();
	} else {
	    m_type = NULLTYPE;
	}
    }
}

// Return true if operands are equal.
bool
as_value::operator==(const as_value& v) const
{
    bool this_nulltype = (m_type == UNDEFINED || m_type == NULLTYPE);
    bool v_nulltype = (v.get_type() == UNDEFINED || v.get_type() == NULLTYPE);
    if (this_nulltype || v_nulltype)
    {
	return this_nulltype == v_nulltype;
    }
    else if (m_type == STRING)
    {
	return m_string_value == v.to_tu_string();
    }
    else if (m_type == NUMBER)
    {
	return m_number_value == v.to_number();
    }
    else if (m_type == BOOLEAN)
    {
	return m_boolean_value == v.to_bool();

    }
    else if (is_object())
    {
    	if ( v.is_object() )
	{
		// compare by reference
		return to_object() == v.to_object();
	}
	else
	{
		// convert this value to a primitive and recurse
		as_value v2 = to_primitive();
		if ( v2.is_object() ) return false;
		else return v2 == v;
		//return to_primitive() == v;
	}
    }
    else
    {
	assert(0);
    }
}

bool
as_value::equals(const as_value& v, as_environment* env) const
{
    bool this_nulltype = (m_type == UNDEFINED || m_type == NULLTYPE);
    bool v_nulltype = (v.get_type() == UNDEFINED || v.get_type() == NULLTYPE);
    if (this_nulltype || v_nulltype)
    {
	return this_nulltype == v_nulltype;
    }
    else if (m_type == STRING)
    {
	return m_string_value == v.to_tu_string(env);
    }
    else if (m_type == NUMBER)
    {
	return m_number_value == v.to_number();
    }
    else if (m_type == BOOLEAN)
    {
	return m_boolean_value == v.to_bool();

    }
    else if (is_object())
    {
    	if ( v.is_object() )
	{
		// compare by reference
		return to_object() == v.to_object();
	}
	else
	{
		// convert this value to a primitive and recurse
		as_value v2 = to_primitive(); // TODO: should forward environment ?
		if ( v2.is_object() ) return false;
		else return v2.equals(v, env);
	}
    }
    else
    {
	assert(0);
    }
}
	
// Return true if operands are not equal.
bool
as_value::operator!=(const as_value& v) const
{
    return ! (*this == v);
}
	
// Sets *this to this string plus the given string.
void
as_value::string_concat(const tu_string& str)
{
    to_tu_string();	// make sure our m_string_value is initialized
    m_type = STRING;
    m_string_value += str;
}

// Drop any ref counts we have; this happens prior to changing our value.
void
as_value::drop_refs()
{
    if (m_type == AS_FUNCTION || m_type == OBJECT )
    {
	if (m_object_value) // should assert here ?
	{
	    m_object_value->drop_ref();
	}
    } 
}

const char*
as_value::typeOf() const
{
	switch(get_type())
	{
		case as_value::UNDEFINED:
			return "undefined"; 

		case as_value::STRING:
			return "string";

		case as_value::NUMBER:
			return "number";

		case as_value::BOOLEAN:
			return "boolean";

		case as_value::OBJECT:
			return "object";

		case as_value::MOVIECLIP:
			return "movieclip";

		case as_value::NULLTYPE:
			return "null";

		case as_value::AS_FUNCTION:
			return "function";

		default:
			assert(0);
	}
}

bool
as_value::strictly_equals(const as_value& v) const
{
	if ( m_type != v.m_type ) return false;

	// using operator== here might not the
	// right thing, we should try to break it.
	return *this == v;
}

std::string
as_value::to_debug_string() const
{
	std::string ret;
	char buf[512];

	switch (m_type)
	{
		case UNDEFINED:
			return "[undefined]";
		case NULLTYPE:
			return "[null]";
		case BOOLEAN:
			sprintf(buf, "[bool:%s]", m_boolean_value ? "true" : "false");
			return buf;
		case OBJECT:
			sprintf(buf, "[object:%p]", m_object_value);
			return buf;
		case AS_FUNCTION:
			sprintf(buf, "[function:%p]", m_object_value);
			return buf;
		case STRING:
			ret = "[string:" + std::string(m_string_value.c_str()) + std::string("]");
			return ret;
		case NUMBER:
			sprintf(buf, "[number:%g]", m_number_value);
			return buf;
		case MOVIECLIP:
			sprintf(buf, "[movieclip:%s]", m_string_value.c_str());
			return buf;
		default:
			assert(0);
	}
}

void
as_value::operator=(const as_value& v)
{
	if (v.m_type == UNDEFINED) set_undefined();
	else if (v.m_type == NULLTYPE) set_null();
	else if (v.m_type == BOOLEAN) set_bool(v.m_boolean_value);
	else if (v.m_type == STRING) set_tu_string(v.m_string_value);
	else if (v.m_type == NUMBER) set_double(v.m_number_value);
	else if (v.m_type == OBJECT) set_as_object(v.m_object_value);

	//TODO: don't use c_str() when m_string_value will be a std::string
	else if (v.m_type == MOVIECLIP) set_sprite(v.m_string_value.c_str());

	else if (v.m_type == AS_FUNCTION) set_as_function(v.m_object_value->to_function());
	else assert(0);
}

} // namespace gnash


// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
