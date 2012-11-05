////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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