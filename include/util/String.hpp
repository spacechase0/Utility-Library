#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
	namespace priv
	{
		template< typename... ARGS >
		void applyManips( std::ios& stream, ARGS&... args )
		{
		}
		
		template< typename T, typename... ARGS >
		inline void applyManips( std::ios& stream, T& t, ARGS&... args )
		{
			t( stream );
			applyManips( stream, t, args... );
		}
		
		template< typename T >
		inline void applyManips( std::ios& stream, T& t )
		{
			t( stream );
		}
	}
	
	std::vector< std::string > tokenize( const std::string& str, const std::string& symbol = "," );
	
	template< typename T, typename... ARGS >
	T fromString( const std::string& str, ARGS&&... args )
	{
		T tmp;
		
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T, typename... ARGS >
	std::string toString( const T& t, ARGS&... args )
	{
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << t;
		return ss.str();
	}
	
	// from/toStringHex -> from/toString( ..., std::hex )
}

#endif // UTIL_STRING_HPP
