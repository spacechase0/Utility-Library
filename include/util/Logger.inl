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

namespace util
{
	// TODO: Find a way to make these use one function
	template< typename T, typename... Args >
	void Logger::operator () ( const std::string& str, T value, Args... args )
	{
		std::string buffer = "";
		for ( auto it = str.begin(); it != str.end(); ++it )
		{
			size_t dist = std::distance( str.begin(), it );
			
			char cc = ( * it );
			if ( dist >= str.size() - 1 )
			{
				buffer += cc;
				break;
			}
			
			char nc = ( * ( it + 1 ) );
			if ( cc == '%' and nc != '%' )
			{
				( * this )( buffer );
				( * this )( util::toString( value ) );
				( * this )( str.substr( dist + 2 ), args... );
				return;
			}
			
			buffer += cc;
		}
		
		( * this )( buffer );
	}

	template< typename T, typename... Args >
	void Logger::log( const std::string& str, T value, Args... args )
	{
		std::string buffer = "";
		for ( auto it = str.begin(); it != str.end(); ++it )
		{
			size_t dist = std::distance( str.begin(), it );
			
			char cc = ( * it );
			if ( dist >= str.size() - 1 )
			{
				buffer += cc;
				break;
			}
			
			char nc = ( * ( it + 1 ) );
			if ( cc == '%' and nc != '%' )
			{
				log( buffer );
				log( util::toString( value ) );
				log( str.substr( dist + 2 ), args... );
				return;
			}
			
			buffer += cc;
		}
		
		log( buffer );
	}

	inline void log( const std::string& str )
	{
		Logger::log( str );
	}

	template< typename... Args >
	void log( const std::string& str, Args... args )
	{
		Logger::log( str, args... );
	}
}
