#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <SFML/System.hpp>
#include <string>
#include <cmath>

namespace util
{
	std::string GetFileContents( const std::string& filename );
	
	template< typename T >
	T Distance( sf::Vector2< T > t1, sf::Vector2< T > t2 )
	{
		return std::sqrt( pow( t2.x - t1.x, 2 ) + pow( t2.y - t1.y, 2 ) );
	}
}

#endif // UTIL_FILE_H
