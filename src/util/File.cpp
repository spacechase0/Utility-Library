#include <util/File.hpp>

#include <fstream>

namespace util
{
	std::string getFileContents( const std::string& filename, bool binary )
	{
		auto mode = std::ifstream::in;
		if ( binary )
		{
			mode |= std::ifstream::binary;
		}
		
		std::ifstream file( filename,mode );
		if ( !file )
		{
			return "";
		}
		
		std::string contents = "";
		while ( !binary )
		{
			std::string line;
			std::getline( file, line );
			if ( !file )
			{
				break;
			}
			
			contents += line;
		}
		while ( binary )
		{
			char c = '\0';
			c = file.get();
			if ( !file )
			{
				break;
			}
			
			contents += c;
		}
		
		return contents;
	}
}
