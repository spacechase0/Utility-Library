namespace util
{
	template< typename ... Args >
	inline void Logger::operator ()( const std::string& str, const Args&... args )
	{
		( * this )( format( str, args... ) );
	}
	
	template< typename ... Args >
	inline void Logger::log( const std::string& str, const Args&... args )
	{
		log( format( str, args... ) );
	}
	
	inline void log( const std::string& str )
	{
		Logger::log( str );
	}

	template< typename... Args >
	inline void log( const std::string& str, const Args&... args )
	{
		Logger::log( str, args... );
	}
}
