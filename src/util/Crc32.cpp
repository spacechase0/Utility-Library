#include "util/Crc32.hpp"

// From RFC 1952
namespace
{
	/* Table of CRCs of all 8-bit messages. */
	unsigned long crc_table[256];

	/* Flag: has the table been computed? Initially false. */
	int crc_table_computed = 0;

	/* Make the table for a fast CRC. */
	void make_crc_table(sf::Uint32 magic)
	{
		unsigned long c;

		int n, k;
		for (n = 0; n < 256; n++) {
			c = (unsigned long) n;
			for (k = 0; k < 8; k++) {
				if (c & 1) {
					c = magic ^ (c >> 1);
				} else {
					c = c >> 1;
				}
			}
			crc_table[n] = c;
		}
		crc_table_computed = 1;
	}

	/*
	Update a running crc with the bytes buf[0..len-1] and return
	the updated crc. The crc should be initialized to zero. Pre- and
	post-conditioning (one's complement) is performed within this
	function so it shouldn't be done by the caller. Usage example:

	unsigned long crc = 0L;

	while (read_buffer(buffer, length) != EOF) {
	crc = update_crc(crc, buffer, length);
	}
	if (crc != original_crc) error();
	*/
	unsigned long update_crc(unsigned long crc,
	const unsigned char *buf, int len, sf::Uint32 magic)
	{
		unsigned long c = crc ^ 0xffffffffL;
		int n;

		make_crc_table( magic );
		for (n = 0; n < len; n++) {
			c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
		}
		return c ^ 0xffffffffL;
	}

	/* Return the CRC of the bytes buf[0..len-1]. */
	unsigned long crc(const unsigned char *buf, int len, sf::Uint32 magic)
	{
		return update_crc(0L, buf, len, magic);
	}
}

namespace util
{
	unsigned long crc32( const std::string& str, sf::Uint32 magic )
	{
		return crc( reinterpret_cast< const unsigned char* >( &str[ 0 ] ), str.length(), magic );
	}
}
