#ifndef UTIL_INIFILE_HPP
#define UTIL_INIFILE_HPP

#include <map>
#include <string>

namespace util
{
	class IniFile
	{
		public:
			typedef std::map< std::string, std::string > Section;
			typedef std::map< std::string, Section > SectionMap;
			
			IniFile();
			IniFile( const std::string& filename );
			
			bool loadFromFile( const std::string& filename );
			bool saveToFile( const std::string& filename, bool saveEmpty = true );
			
			const Section& operator[] ( const std::string& str ) const;
			Section& operator[] ( const std::string& str );
			
			const SectionMap& getSections() const;
			SectionMap& getSections();
			
			void deleteSection( const std::string& sectionName );
			
		private:
			SectionMap sections;
			static Section emptySection;
	};
}

#endif // UTIL_INIFILE_HPP
