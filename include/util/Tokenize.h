#ifndef UTIL_TOKENIZE_H
#define UTIL_TOKENIZE_H

#include <string>
#include <vector>

namespace util
{
	std::vector< std::string > Tokenize( const std::string& str, const std::string& symbol = "," );
}

#endif // UTIL_TOKENIZE_H
