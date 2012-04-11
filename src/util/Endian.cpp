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

#include <util/Endian.h>

namespace util
{
	float SwapFloat( float f )
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

	double SwapDouble( double d )
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
