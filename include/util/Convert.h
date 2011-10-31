////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2011 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef UTIL_CONVERT_H
#define UTIL_CONVERT_H

#include <sstream>
#include <iomanip>
#include <string>

namespace util
{
	template< typename T >
	T FromString( const std::string& str )
	{
		T tmp;
		
		std::stringstream ss;
		ss << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T >
	T FromStringHex( const std::string& str )
	{
		T tmp;
		
		std::stringstream ss;
		ss << std::hex << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T >
	std::string ToString( const T& t )
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
	
	template< typename T >
	std::string ToStringHex( const T& t )
	{
		std::stringstream ss;
		ss << std::hex << t;
		return ss.str();
	}
}

#endif // UTIL_CONVERT_H
