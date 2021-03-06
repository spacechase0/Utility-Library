#ifndef ENDIAN_HPP
#define ENDIAN_HPP

#include <SFML/System.hpp>
#include <type_traits>

// http://www.gamedev.net/page/resources/_/reference/programming/sweet-snippets/writing-endian-independent-code-in-c-r2091

namespace util
{
	const sf::Uint16 ENDIAN_TEST = 0x0001;
	const bool BIG_ENDIAN = ( ENDIAN_TEST == 256 );
	const bool LITTLE_ENDIAN = ( ENDIAN_TEST == 1 );
	
	template< typename T, size_t S = sizeof( T ) >
	typename std::enable_if< std::is_integral< T >::value, T >::type
	swapBytes( T t )
	{
		T toReturn = 0;
		
		for ( size_t i = 0; i < S; ++i )
		{
			sf::Uint8 byte = ( t >> ( i * 8 ) ) & 0xff;
			toReturn += byte << ( ( S - 1 - i ) * 8 );
		}
		
		return toReturn;
	}
	
	template< typename T, size_t S = sizeof( T ) >
	typename std::enable_if< std::is_floating_point< T >::value, T >::type
	swapBytes( T t )
	{
		union
		{
			T f2;
			unsigned char b[ S ];
		} dat1, dat2;

		dat1.f2 = t;
		for ( size_t i = 0; i < S; ++i )
		{
			dat2.b[ i ] = dat1.b[ S - 1 - i ];
		}
		
		return dat2.f2;
	}
	
	template< typename T >
	T swapBytes2( T t )
	{
		unsigned char byte1, byte2;

		byte1 = ( t >> 0 ) & 255;
		byte2 = ( t >> 8 ) & 255;

		return ( byte1 << 8 ) + ( byte2 << 0 );
	}

	template< typename T >
	T swapBytes4( T t )
	{
		unsigned char byte1, byte2, byte3, byte4;

		byte1 = ( t >>  0 ) & 255;
		byte2 = ( t >>  8 ) & 255;
		byte3 = ( t >> 16 ) & 255;
		byte4 = ( t >> 24 ) & 255;

		return ( ( T ) byte1 << 24 ) + ( ( T ) byte2 << 16 ) + ( ( T ) byte3 << 8 ) + ( ( T ) byte4 << 0 );
	}

	template< typename T >
	T swapBytes8( T t )
	{
		unsigned char byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8;

		byte1 = ( t >>  0 ) & 255;
		byte2 = ( t >>  8 ) & 255;
		byte3 = ( t >> 16 ) & 255;
		byte4 = ( t >> 24 ) & 255;
		byte5 = ( t >> 32 ) & 255;
		byte6 = ( t >> 40 ) & 255;
		byte7 = ( t >> 48 ) & 255;
		byte8 = ( t >> 56 ) & 255;
		
		T result = ( ( T ) byte1 << 56 ) + ( ( T ) byte2 << 48 ) + ( ( T ) byte3 << 40 ) + ( ( T ) byte4 << 32 );
		result  += ( ( T ) byte5 << 24 ) + ( ( T ) byte6 << 16 ) + ( ( T ) byte7 <<  8 ) + ( ( T ) byte8 <<  0 );
		return result;
	}

	float swapFloat( float f );
	double swapDouble( double d );
}

#endif // ENDIAN_HPP
