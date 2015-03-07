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
