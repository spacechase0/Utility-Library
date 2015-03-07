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
