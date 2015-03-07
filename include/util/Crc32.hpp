#ifndef UTIL_CRC32_HPP
#define UTIL_CRC32_HPP

#include <SFML/Config.hpp>
#include <string>

namespace util
{
	unsigned long crc32( const std::string& str, sf::Uint32 magic = 0xedb88320L );
}

#endif // UTIL_CRC32_HPP
