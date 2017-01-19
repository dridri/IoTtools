/*
 * IoTtools
 * Copyright (C) 2016 Adrien Aubry (drich)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef DEBUG_H
#define DEBUG_H

#include <string.h>

#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <mutex>
#include <tuple>
#include <pthread.h>
#include <cxxabi.h>

class Debug
{
public:
	Debug() {
	}
	~Debug() {
		if ( sEnabled ) {
			std::string s = mSS.str() + "\n";
			printf( "%s", s.c_str() );
			fflush( stdout );
		}
	}
	template<typename T> Debug& operator<<( const T& t ) {
		mSS << t;
		return *this;
	}

	static bool enabled() { return sEnabled; }
	static void setEnabled( bool en ) { sEnabled = en; }

private:
	std::stringstream mSS;
	static bool sEnabled;
};


#ifndef __DBG_CLASS
static inline std::string className(const std::string& prettyFunction)
{
	size_t parenthesis = prettyFunction.find("(");
	size_t colons = prettyFunction.substr( 0, parenthesis ).rfind("::");
	if (colons == std::string::npos)
		return "<none>";
	size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
	size_t end = colons - begin;
	return "\x1B[32m" + prettyFunction.substr(begin,end) + "\x1B[0m";
}

#pragma GCC system_header // HACK Disable unused-function warnings
static std::string self_thread() {
	std::stringstream ret;
	char name[128];
	pthread_getname_np( pthread_self(), name, sizeof(name)-1 );
	ret << "\x1B[33m" << "[" << name << "] " << "\x1B[0m";
	return ret.str();
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)
#define __FUNCTION_NAME__ ( std::string("\x1B[94m") + __FUNCTION__ + "\x1B[0m" )

#define gDebug() Debug() << self_thread() << __CLASS_NAME__ << "::" << __FUNCTION_NAME__ << "() "

#pragma GCC system_header // HACK Disable unused-function warnings
static void fDebug_base( std::stringstream& out, const char* end, bool f ) {
	out << " " << end;
}

template<typename Arg1, typename... Args> static void fDebug_base( std::stringstream& out, const char* end, bool first, const Arg1& arg1, const Args&... args ) {
	char* type = abi::__cxa_demangle(typeid(arg1).name(), nullptr, nullptr, nullptr);
	char cap = 0;
	std::string color = "\x1B[0m";
	if ( strstr( type, "char" ) ) {
		if ( strstr( type, "*" ) || ( strstr( type, "[" ) && strstr( type, "]" ) ) || strstr( type, "string" ) ) {
			cap = '\"';
			color = "\x1B[31m";
		} else {
			cap = '\'';
			color = "\x1B[31m";
		}
	}
	free(type);

	std::stringstream arg_ss;
	arg_ss << arg1;
	if ( arg_ss.str()[0] >= '0' && arg_ss.str()[0] <= '9' ) {
		color = "\x1B[36m";
	}

	if (!first ) {
		out << ", ";
	}
	std::stringstream ss;
	ss << color;
	if ( cap ) ss << cap;
	ss << arg_ss.str();
	if ( cap ) ss << cap;
	ss << "\x1B[0m";
	out << ss.str();
	fDebug_base( out, end, false, args... );
}

#pragma GCC system_header // HACK Disable unused-function warnings
template<typename... Args> static std::string fDebug_top( const Args&... args ) {
	if ( not Debug::enabled() ) {
		return "";
	}
	std::stringstream out;
	if ( sizeof...(args) == 0 ) {
		out << ")";
	} else {
		out << " ";
		fDebug_base( out, ")", true, args... );
	}
	return out.str();
}

#define fDebug( ... ) { Debug dbg; dbg << self_thread() << __CLASS_NAME__ << "::" << __FUNCTION_NAME__ << "("; dbg << fDebug_top( __VA_ARGS__ ); }

#ifndef fDebug
extern void fDebug(); // KDevelop hack
#endif fDebug

#endif // __DBG_CLASS

#endif // DEBUG_H
