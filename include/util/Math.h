#ifndef UTIL_MATH_H
#define UTIL_MATH_H

namespace util
{
	static const float pi = 3.14159265;
	inline float RadiansToDegrees( float radians )
	{
		return radians * ( 180 / pi );
	}
	inline float DegreesToRadians( float degrees )
	{
		return degrees * ( pi / 180 );
	}
}

#endif // UTIL_MATH_H
