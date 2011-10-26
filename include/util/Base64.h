#ifndef UTIL_BASE64_H
#define UTIL_BASE64_H

#include <string>

namespace util
{
	namespace b64
	{
		std::string Encode( unsigned char const* , unsigned int len );
		std::string Decode( const std::string& s );
	}
}

#endif // UTIL_BASE64_H
