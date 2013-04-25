////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2013 Chase Warrington (staff@spacechase0.com)
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

#include <util/IniFile.hpp>
#include <fstream>

namespace util
{
	IniFile::Section IniFile::emptySection;
	
	IniFile::IniFile()
	{
	}
	
	IniFile::IniFile( const std::string& filename )
	{
		loadFromFile( filename );
	}
	
	bool IniFile::loadFromFile( const std::string& filename )
	{
		std::fstream file( filename, std::fstream::in );
		if ( !file )
		{
			return false;
		}
		
		std::string currentName = "";
		Section currentSection;
		while ( true )
		{
			std::string line;
			std::getline( file, line );
			if ( !file )
			{
				( * this )[ currentName ] = currentSection;
				if ( file.eof() )
				{
					return true;
				}
				else
				{
					return false;
				}
				break;
			}
			
			if ( line.find( ";" ) != std::string::npos )
			{
				// TO DO: Check for backslash escaping
				line = line.substr( 0, line.find( ";" ) );
			}
			
			// I don't want something like this to work:
			// [some=thing
			if ( line[ 0 ] == '[' )
			{
				if ( line[ line.length() - 1 ] == ']' )
				{
					( * this )[ currentName ] = currentSection;
					currentName = line.substr( 1, line.length() - 2 );
					currentSection = Section();
				}
			}
			else if ( line.find( "=" ) != std::string::npos )
			{
				std::string name = line.substr( 0, line.find( "=" ) );
				std::string value = line.substr( line.find( "=" ) + 1 );
				
				currentSection.push_back( std::pair< std::string, std::string >( name, value ) );
			}
		}
		
		return true;
	}
	
	bool IniFile::saveToFile( const std::string& filename, bool saveEmpty )
	{
		std::fstream file( filename, std::fstream::out | std::fstream::trunc );
		if ( !file )
		{
			return false;
		}
		
		for ( auto it = sections.begin(); it != sections.end(); ++it )
		{
			if ( it->first.size() == 0 and !saveEmpty )
			{
				continue;
			}
			
			file << "[" << it->first << "]" << std::endl;
			for ( auto it2 = it->second.begin(); it2 != it->second.end(); ++it2 )
			{
				file << it2->first << "=" << it2->second << std::endl;
			}
		}
		
		file.close();
		return true;
	}
	
	const IniFile::Section& IniFile::operator[] ( const std::string& str ) const
	{
		if ( sections.find( str ) == sections.end() )
		{
			return emptySection;
		}
		
		return sections.at( str );
	}
	
	IniFile::Section& IniFile::operator[] ( const std::string& str )
	{
		if ( sections.find( str ) == sections.end() )
		{
			sections.push_back( std::pair< std::string, Section >( str, Section() ) );
		}
		
		return sections[ str ];
	}
	
	const IniFile::SectionMap& IniFile::getSections() const
	{
		return sections;
	}
	
	IniFile::SectionMap& IniFile::getSections()
	{
		return sections;
	}
	
	void IniFile::deleteSection( const std::string& sectionName )
	{
		if ( sections.find( sectionName ) != sections.end() )
		{
			sections.erase( sections.find( sectionName ) );
		}
	}
}
