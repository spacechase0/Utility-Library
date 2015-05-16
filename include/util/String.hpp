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
	
	inline std::string format( const std::string& str );
	template< typename T, typename... Args >
	std::string format( const std::string& str, T value, Args... args );
}

#include <util/String.inl>

#endif // UTIL_STRING_HPP
