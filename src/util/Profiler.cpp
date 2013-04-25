#include "util/Profiler.hpp"

#include <SFML/System/Lock.hpp>

namespace util
{
	ProfilerObject::ProfileSection::ProfileSection()
	   : parent( NULL ),
	     name( "root" )
	{
	}
	
	ProfilerObject::ProfilerObject()
	   : active( NULL ),
	     parent( NULL )
	{
		restart();
	}
	
	void ProfilerObject::restart()
	{
		previous = profile;
		profile = ProfileSection();
		
		active = &profile;
		parent = &profile;
		
		clock.restart();
	}
	
	void ProfilerObject::startSection( const std::string& name, bool descend )
	{
		if ( !active )
		{
			return;
		}
		
		if ( !descend )
		{
			endSection();
		}
		
		std::shared_ptr< ProfileSection > section( new ProfileSection() );
		section->parent = active;
		section->name = name;
		
		parent = active;
		parent->sections.push_back( section );
		active = section.get();
	}
	
	void ProfilerObject::endSection()
	{
		if ( !active )
		{
			return;
		}
		
		active->time = clock.restart();
		for ( auto it = active->sections.begin(); it != active->sections.end(); ++it )
		{
			active->time += it->get()->time;
		}
		active = NULL;
		
		if ( parent )
		{
			active = parent;
			parent = active->parent;
		}
		
		if ( !parent )
		{
			parent = &profile;
		}
	}
	
	auto ProfilerObject::getPreviousSections() const -> const ProfileSection&
	{
		return previous;
	}
	
	sf::ThreadLocalPtr< ProfilerObject > ProfilerStatic::profiler;
	std::vector< std::shared_ptr< ProfilerObject > > ProfilerStatic::profilers;
	sf::Mutex ProfilerStatic::mutex;
	
	void ProfilerStatic::restart()
	{
		initProfiler();
		profiler->restart();
	}
	
	void ProfilerStatic::startSection( const std::string& name, bool descend )
	{
		initProfiler();
		profiler->startSection( name, descend );
	}
	
	void ProfilerStatic::endSection()
	{
		initProfiler();
		profiler->endSection();
	}
	
	const ProfilerObject::ProfileSection& ProfilerStatic::getPreviousSections()
	{
		initProfiler();
		return profiler->getPreviousSections();
	}
	
	void ProfilerStatic::initProfiler()
	{
		if ( !profiler )
		{
			ProfilerObject* theProfiler = new ProfilerObject();
			profiler = theProfiler;
			{
				sf::Lock lock( mutex );
				profilers.push_back( std::shared_ptr< ProfilerObject >( theProfiler ) );
			}
		}
	}
}
