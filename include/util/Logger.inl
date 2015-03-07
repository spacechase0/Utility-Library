namespace util
{
	// TODO: Find a way to make these use one function
	template< typename T, typename... Args >
	void Logger::operator () ( const std::string& str, T value, Args... args )
	{
		std::string buffer = "";
		for ( auto it = str.begin(); it != str.end(); ++it )
		{
			size_t dist = std::distance( str.begin(), it );
			
			char cc = ( * it );
			if ( dist >= str.size() - 1 )
			{
				buffer += cc;
				break;
			}
			
			char nc = ( * ( it + 1 ) );
			if ( cc == '%' and nc != '%' )
			{
				( * this )( buffer );
				( * this )( util::toString( value ) );
				( * this )( str.substr( dist + 2 ), args... );
				return;
			}
			
			buffer += cc;
		}
		
		( * this )( buffer );
	}

	template< typename T, typename... Args >
	void Logger::log( const std::string& str, T value, Args... args )
	{
		std::string buffer = "";
		for ( auto it = str.begin(); it != str.end(); ++it )
		{
			size_t dist = std::distance( str.begin(), it );
			
			char cc = ( * it );
			if ( dist >= str.size() - 1 )
			{
				buffer += cc;
				break;
			}
			
			char nc = ( * ( it + 1 ) );
			if ( cc == '%' and nc != '%' )
			{
				log( buffer );
				log( util::toString( value ) );
				log( str.substr( dist + 2 ), args... );
				return;
			}
			
			buffer += cc;
		}
		
		log( buffer );
	}

	inline void log( const std::string& str )
	{
		Logger::log( str );
	}

	template< typename... Args >
	void log( const std::string& str, Args... args )
	{
		Logger::log( str, args... );
	}
}
