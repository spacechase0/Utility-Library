#ifndef UTIL_STREAMBUFFERPRESERVER_HPP
#define UTIL_STREAMBUFFERPRESERVER_HPP

#include <ios>
#include <streambuf>

namespace util
{
	class StreamBufferPreserver
	{
		public:
			StreamBufferPreserver( std::ios& theStream );
			~StreamBufferPreserver();
		
		private:
			std::ios& stream;
			std::streambuf* oldBuffer;
	};
}

#endif // UTIL_STREAMBUFFERPRESERVER_HPP
