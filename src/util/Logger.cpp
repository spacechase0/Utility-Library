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

#include "util/Logger.hpp"

#include <SFML/Config.hpp>
#ifndef SFML_SYSTEM_WINDOWS
	#error Implement proper thread ID code later, or mutex protected ID
#endif

#include <ctime>
#include <SFML/System/Lock.hpp>
#include <stdexcept>
#include <util/String.hpp>
#include <windows.h>

namespace util
{
	sf::ThreadLocalPtr< Logger > Logger::threadLogger;
	std::map< int, std::shared_ptr< Logger > > Logger::threadLoggers;
	sf::Mutex Logger::threadMutex;

	Logger::Logger( const std::string& name )
	{
		file.open( /*"data/logs/" +*/ name /*+ ".txt"*/, std::fstream::out | std::fstream::trunc );
		if ( !file )
		{
			// We can't exactly use a log for this... What if it fails to open, too?
			throw std::runtime_error( "Failed to open \""/*data/logs/"*/ + name + "\"!" );
		}
	}

	void Logger::operator () ( const std::string& str )
	{
		sf::Lock lock( mutex );
		file << str << std::flush;
	}

	void Logger::setName( const std::string& name, const std::string& file )
	{
		if ( !threadLogger )
		{
			openThreadLog( file );
		}
		
		log( "##### NAME = \"" + name + "\" #####\n" );
	}

	void Logger::log( const std::string& str )
	{
		if ( !threadLogger )
		{
			openThreadLog( "thread-" + util::toString( GetCurrentThreadId() ) );
		}
		
		( * threadLogger )( str );
	}
	
	void Logger::openThreadLog( const std::string& name )
	{
		Logger* theLog = new Logger( name );
		threadLogger = theLog;
		{
			sf::Lock lock( threadMutex );
			threadLoggers.insert( std::make_pair( GetCurrentThreadId(), std::shared_ptr< Logger >( theLog ) ) );
		}
	}
}
