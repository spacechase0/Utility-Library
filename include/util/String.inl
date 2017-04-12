#include <cctype>
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
	
        inline void outputN( std::ostream& o, int curr )
        {
        }

        template< typename T, typename... Ts >
        void outputN( std::ostream& o, int curr, const T& t, const Ts&... ts )
        {
            if ( curr == 0 )
            {
                o << t;
            }
            else outputN( o, --curr, ts... );
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

    template< typename... Args >
    void formatStream( std::ostream& o, const std::string& str_, const Args&... args )
    {
        const char* str = str_.c_str();
        int baseVar = 0;
        for ( ; str[ 0 ] != '\0'; ++str )
        {
            if ( str[ 0 ] == '\\' )
            {
                if ( str[ 1 ] != '\0' )
                {
                    o << str[ 1 ];
                    ++str;
                }
            }
            else if ( str[ 0 ] == '$' )
            {
                int var = baseVar;
                char next = std::toupper( str[ 1 ] );
                if ( next >= '0' && next <= '9' )
                {
                    var = next - '0';
                    ++str;
                }
                else ++baseVar;

                priv::outputN( o, var, args... );
            }
            else o << str[ 0 ];
        }
    }
    
    template< typename... Args >
	std::string format( const std::string& str, const Args&... args )
	{
	    std::ostringstream ss;
	    formatStream( ss, str, args... );
	    return ss.str();
	}
}
