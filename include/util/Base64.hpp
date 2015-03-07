#ifndef UTIL_BASE64_HPP
#define UTIL_BASE64_HPP

#include <string>

namespace util
{
	namespace b64
	{
		std::string encode( unsigned char const* , unsigned int len );
		std::string decode( const std::string& s );
	}
}

#endif // UTIL_BASE64_HPP
