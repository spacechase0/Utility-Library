#ifndef UTIL_FILE_HPP
#define UTIL_FILE_HPP

#include <string>

namespace util
{
	std::string getFileContents( const std::string& filename, bool binary = false );
}

#endif // UTIL_FILE_HPP
