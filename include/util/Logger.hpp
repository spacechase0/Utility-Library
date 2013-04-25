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

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/ThreadLocalPtr.hpp>
#include <string>
#include <util/Convert.h>

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
			
			// Static interface - uses thread ID
			static void setName( const std::string& name, const std::string& file );
			static void log( const std::string& str );
			template< typename T, typename ... Args >
			static void log( const std::string& str, T t, Args... args );
			
		private:
			// Non-static data
			std::fstream file;
			mutable sf::Mutex mutex;
			
			// Static data
			static sf::ThreadLocalPtr< Logger > threadLogger;
			static std::map< int, std::shared_ptr< Logger > > threadLoggers; // TODO: Make this use std::unique_ptr
			static sf::Mutex threadMutex;
			
			static void openThreadLog( const std::string& name );
	};
	
	inline void log( const std::string& str );
	template< typename... Args >
	void log( const std::string& str, Args... args );
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
