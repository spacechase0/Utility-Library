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

#ifndef UTIL_MATH_HPP
#define UTIL_MATH_HPP

namespace util
{
	constexpr float PI = 3.14159265;
	
	inline float radiansToDegrees( float radians )
	{
		return radians * ( 180 / PI );
	}
	
	inline float degreesToRadians( float degrees )
	{
		return degrees * ( PI / 180 );
	}
	
	template< typename T >
	T distance( sf::Vector2< T > t1, sf::Vector2< T > t2 )
	{
		return std::sqrt( pow( t2.x - t1.x, 2 ) + pow( t2.y - t1.y, 2 ) );
	}
}

#endif // UTIL_MATH_HPP
