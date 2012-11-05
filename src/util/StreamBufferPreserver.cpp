#include "util/StreamBufferPreserver.hpp"

namespace util
{
	StreamBufferPreserver::StreamBufferPreserver( std::ios& theStream )
	   : stream( theStream ),
		 oldBuffer( theStream.rdbuf() )
	{
	}
	
	StreamBufferPreserver::~StreamBufferPreserver()
	{
		stream.rdbuf( oldBuffer );
	}
}
