#include <util/String.hpp>

namespace util
{
	std::vector< std::string > tokenize( const std::string& str, const std::string& symbol )
	{
		std::vector< std::string > toReturn;

		size_t start = 0;
		for ( size_t found = str.find( symbol, start ); found != std::string::npos; found = str.find( symbol, start ) )
		{
			toReturn.push_back( str.substr( start, found - start ) );
			start = found + symbol.length();
		}
		toReturn.push_back( str.substr( start ) );

		return toReturn;
	}
}
