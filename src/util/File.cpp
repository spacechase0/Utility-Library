#include <util/Misc.h>

#include <fstream>

namespace util
{
	std::string GetFileContents( const std::string& filename )
	{
		std::fstream file( filename, std::fstream::in );
		if ( !file )
		{
			return "";
		}
		
		std::string contents = "";
		while ( true )
		{
			std::string line;
			std::getline( file, line );
			if ( file.eof() )
			{
				break;
			}
			
			contents += line;
		}
		
		return contents;
	}
}
