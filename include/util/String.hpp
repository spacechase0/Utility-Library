////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2013 Chase Warrington (staff@spacechase0.com)
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

#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
	namespace priv
	{
		template< typename... ARGS >
		void applyManips( std::ios& stream, ARGS&... args )
		{
		}
		
		template< typename T, typename... ARGS >
		inline void applyManips( std::ios& stream, T& t, ARGS&... args )
		{
			t( stream );
			applyManips( stream, t, args... );
		}
		
		template< typename T >
		inline void applyManips( std::ios& stream, T& t )
		{
			t( stream );
		}
	}
	
	std::vector< std::string > tokenize( const std::string& str, const std::string& symbol = "," );
	
	template< typename T, typename... ARGS >
	T fromString( const std::string& str, ARGS&&... args )
	{
		T tmp;
		
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T, typename... ARGS >
	std::string toString( const T& t, ARGS&... args )
	{
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << t;
		return ss.str();
	}
	
	// from/toStringHex -> from/toString( ..., std::hex )
}

#endif // UTIL_STRING_HPP
