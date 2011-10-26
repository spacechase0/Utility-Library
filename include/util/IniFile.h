#ifndef UTIL_INIFILE_H
#define UTIL_INIFILE_H

#include <string>

#include "util/unsorted_map.h"

namespace util
{
	class IniFile
	{
		public:
			typedef util::unsorted_map< std::string, std::string > Section;
			typedef util::unsorted_map< std::string, Section > SectionMap;
			
			IniFile();
			IniFile( const std::string& filename );
			
			bool LoadFromFile( const std::string& filename );
			bool SaveToFile( const std::string& filename, bool saveEmpty = true );
			
			const Section& operator[] ( const std::string& str ) const;
			Section& operator[] ( const std::string& str );
			
			const SectionMap& GetSections() const;
			SectionMap& GetSections();
			
			void DeleteSection( const std::string& sectionName );
			
		private:
			SectionMap sections;
			static Section emptySection;
	};
}

#endif // UTIL_INIFILE_H
