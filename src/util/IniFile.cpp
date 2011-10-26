#include <util/IniFile.h>
#include <fstream>

namespace util
{
	IniFile::Section IniFile::emptySection;
	
	IniFile::IniFile()
	{
	}
	
	IniFile::IniFile( const std::string& filename )
	{
		LoadFromFile( filename );
	}
	
	bool IniFile::LoadFromFile( const std::string& filename )
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
	
	bool IniFile::SaveToFile( const std::string& filename, bool saveEmpty )
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
	
	const IniFile::SectionMap& IniFile::GetSections() const
	{
		return sections;
	}
	
	IniFile::SectionMap& IniFile::GetSections()
	{
		return sections;
	}
	
	void IniFile::DeleteSection( const std::string& sectionName )
	{
		if ( sections.find( sectionName ) != sections.end() )
		{
			sections.erase( sections.find( sectionName ) );
		}
	}
}
