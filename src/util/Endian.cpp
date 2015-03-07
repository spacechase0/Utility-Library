#include <util/Endian.hpp>

namespace util
{
	float swapFloat( float f )
	{
		union
		{
			float f2;
			unsigned char b[ 4 ];
		} dat1, dat2;

		dat1.f2 = f;
		dat2.b[ 0 ] = dat1.b[ 3 ];
		dat2.b[ 1 ] = dat1.b[ 2 ];
		dat2.b[ 2 ] = dat1.b[ 1 ];
		dat2.b[ 3 ] = dat1.b[ 0 ];
		return dat2.f2;
	}

	double swapDouble( double d )
	{
		union
		{
			double d2;
			unsigned char b[ 8 ];
		} dat1, dat2;

		dat1.d2 = d;
		dat2.b[ 0 ] = dat1.b[ 7 ];
		dat2.b[ 1 ] = dat1.b[ 6 ];
		dat2.b[ 2 ] = dat1.b[ 5 ];
		dat2.b[ 3 ] = dat1.b[ 4 ];
		dat2.b[ 4 ] = dat1.b[ 3 ];
		dat2.b[ 5 ] = dat1.b[ 2 ];
		dat2.b[ 6 ] = dat1.b[ 1 ];
		dat2.b[ 7 ] = dat1.b[ 0 ];
		return dat2.d2;
	}
}
