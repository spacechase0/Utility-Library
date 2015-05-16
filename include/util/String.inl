#include <iomanip>
#include <ios>
#include <sstream>

namespace util
{
	namespace priv
	{
		template< typename... ARGS >
		void applyManips( std::ios& stream, ARGS&... args )
		{
		}
		
		template< typename T, typename... ARGS >
		inline void applyManips( std::ios& stream, T& t, ARGS&... args )
		{
			t( stream );
			applyManips( stream, t, args... );
		}
		
		template< typename T >
		inline void applyManips( std::ios& stream, T& t )
		{
			t( stream );
		}
	}
	
	template< typename T, typename... ARGS >
	T fromString( const std::string& str, ARGS&&... args )
	{
		T tmp;
		
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << str;
		ss >> tmp;
		
		return tmp;
	}
	
	template< typename T, typename... ARGS >
	std::string toString( const T& t, ARGS&... args )
	{
		std::stringstream ss;
		priv::applyManips( ss, args... );
		ss << t;
		return ss.str();
	}
	
	inline std::string format( const std::string& str )
	{
		return str;
	}
	
	template< typename T, typename... Args >
	std::string format( const std::string& str, T value, Args... args )
	{
		// TODO: Make this use a single std::stringstream
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
				buffer += util::toString( value );
				return buffer + format( str.substr( dist + 2 ), args... );
			}
			
			buffer += cc;
		}
		
		return buffer;
	}
}
