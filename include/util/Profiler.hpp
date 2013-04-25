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

#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <memory>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/ThreadLocalPtr.hpp>
#include <string>
#include <vector>

namespace util
{
	class ProfilerObject
	{
		public:
			struct ProfileSection
			{
				public:
					ProfileSection();
					
					ProfileSection* parent;
					std::string name;
					std::vector< std::shared_ptr< ProfileSection > > sections;
					sf::Time time;
			};
			
			ProfilerObject();
			
			void restart();
			void startSection( const std::string& name, bool descend );
			void endSection();
			
			const ProfileSection& getPreviousSections() const;
		
		private:
			ProfileSection profile;
			ProfileSection* active;
			ProfileSection* parent;
			sf::Clock clock;
			
			ProfileSection previous;
	};

	class ProfilerStatic
	{
		public:
			static void restart();
			static void startSection( const std::string& name, bool descend );
			static void endSection();
			
			static const ProfilerObject::ProfileSection& getPreviousSections();
		
		private:
			static sf::ThreadLocalPtr< ProfilerObject > profiler;
			static std::vector< std::shared_ptr< ProfilerObject > > profilers;
			static sf::Mutex mutex;
			
			static void initProfiler();
	};
	
	typedef ProfilerStatic Profiler;
}

#ifndef UTIL_REMOVE_GLOBAL_PROFILER
typedef util::Profiler Profiler;
#endif

#endif // PROFILER_HPP
