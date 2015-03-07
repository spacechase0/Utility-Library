#include "util/Logger.hpp"

#include <SFML/Config.hpp>
#ifndef SFML_SYSTEM_WINDOWS
	#error Implement proper thread ID code later, or mutex protected ID
#endif

#include <ctime>
#include <iostream>
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
	   : outputConsole( true )
	{
		file.open( /*"data/logs/" +*/ name /*+ ".txt"*/, std::fstream::out | std::fstream::trunc );
		if ( !file )
		{
			// We can't exactly use a log for this... What if it fails to open, too?
			std::cout << "Failed to open \"" + name + "\"!" << std::endl;
			throw std::runtime_error( "Failed to open \"" + name + "\"!" );
		}
	}

	void Logger::operator () ( const std::string& str )
	{
		if ( outputConsole )
		{
			std::cout << str;
		}
		
		sf::Lock lock( mutex );
		file << str << std::flush;
	}
	
	void Logger::setConsoleOutput( bool theOutputConsole )
	{
		outputConsole = theOutputConsole;
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
	
	void Logger::setThreadConsoleOutput( bool theOutputConsole )
	{
		threadLogger->setConsoleOutput( theOutputConsole );
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
