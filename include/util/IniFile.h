////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2011 Chase Warrington (staff@spacechase0.com)
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
