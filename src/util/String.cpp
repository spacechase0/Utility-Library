////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
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

#include <util/String.hpp>

namespace util
{
	std::vector< std::string > tokenize( const std::string& str, const std::string& symbol )
	{
		std::vector< std::string > toReturn;

		size_t start = 0;
		for ( size_t found = str.find( symbol, start ); found != std::string::npos; found = str.find( symbol, start ) )
		{
			toReturn.push_back( str.substr( start, found - start ) );
			start = found + symbol.length();
		}
		toReturn.push_back( str.substr( start ) );

		return toReturn;
	}
}