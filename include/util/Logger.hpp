#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/ThreadLocalPtr.hpp>
#include <string>
#include <util/String.hpp>

namespace util
{
	class Logger
	{
		public:
			// Non-static version
			Logger( const std::string& name );
			
			void operator () ( const std::string& str );
			template< typename T, typename... Args >
			void operator ()( const std::string& str, T t, Args... args );
			
			void setConsoleOutput( bool theOutputConsole );
			
			// Static interface - uses thread ID
			static void setName( const std::string& name, const std::string& file );
			static void log( const std::string& str );
			template< typename T, typename ... Args >
			inline static void log( const std::string& str, T t, Args... args );
			static void setThreadConsoleOutput( bool theOutputConsole );
			
		private:
			// Non-static data
			std::fstream file;
			mutable sf::Mutex mutex;
			bool outputConsole;
			
			// Static data
			static sf::ThreadLocalPtr< Logger > threadLogger;
			static std::map< int, std::shared_ptr< Logger > > threadLoggers; // TODO: Make this use std::unique_ptr
			static sf::Mutex threadMutex;
			
			static void openThreadLog( const std::string& name );
	};
	
	inline void log( const std::string& str );
	template< typename... Args >
	inline void log( const std::string& str, Args... args );
}

#include "Logger.inl"

#ifndef UTIL_REMOVE_GLOBAL_LOG_FUNCTION
inline void log( const std::string& str )
{
	util::log( str );
}

template< typename... Args >
inline void log( const std::string& str, Args... args )
{
	util::log( str, args... );
}
#endif

#endif // LOGGER_HPP
