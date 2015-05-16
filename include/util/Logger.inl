namespace util
{
	template< typename T, typename ... Args >
	inline void Logger::operator ()( const std::string& str, T t, Args... args )
	{
		log( format( str, t, args... ) );
	}
	
	template< typename T, typename ... Args >
	inline void Logger::log( const std::string& str, T t, Args... args )
	{
		log( format( str, t, args... ) );
	}
	
	inline void log( const std::string& str )
	{
		Logger::log( str );
	}

	template< typename... Args >
	inline void log( const std::string& str, Args... args )
	{
		Logger::log( str, args... );
	}
}
