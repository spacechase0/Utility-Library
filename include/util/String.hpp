#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <string>
#include <vector>

namespace util
{
	std::vector< std::string > tokenize( const std::string& str, const std::string& symbol = "," );
	
	template< typename T, typename... ARGS >
	T fromString( const std::string& str, ARGS&&... args );
	
	template< typename T, typename... ARGS >
	std::string toString( const T& t, ARGS&... args );
	
	// from/toStringHex -> from/toString( ..., std::hex )
	
	template< typename... Args >
	void formatStream( std::ostream& o, const std::string& str, const Args&... args );
	template< typename... Args >
	std::string format( const std::string& str, const Args&... args );
}

#include <util/String.inl>

#endif // UTIL_STRING_HPP
