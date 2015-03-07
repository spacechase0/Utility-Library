#ifndef UTIL_BINDTUPLE_HPP
#define UTIL_BINDTUPLE_HPP

#include <functional>
#include <tuple>

// TO DO: Separate into two files

namespace util
{
	// http://stackoverflow.com/questions/10766112/c11-i-can-go-from-multiple-args-to-tuple-but-can-i-go-from-tuple-to-multiple
	namespace priv
	{
		template< typename FUNC, typename TUPLE, typename SIG, bool DONE, int MAX, int... N >
		struct TupleBinder
		{
			static std::function< SIG > bindTuple( FUNC func, TUPLE&& tuple )
			{
				return TupleBinder< FUNC, TUPLE, SIG, MAX == ( 1 + sizeof...( N ) ), MAX, N..., sizeof...( N ) >::bindTuple( func, std::forward< TUPLE >( tuple ) );
			}
		};
		
		template< typename FUNC, typename TUPLE, typename SIG, int MAX, int... N >
		struct TupleBinder< FUNC, TUPLE, SIG, true, MAX, N... >
		{
			static std::function< SIG > bindTuple( FUNC func, TUPLE&& tuple )
			{
				return std::bind( func, std::get< N >( std::forward< TUPLE >( tuple ) )... );
			}
		};
	}

	template< typename FUNC, typename TUPLE, typename SIG >
	void bindTuple( FUNC func, TUPLE&& tuple, std::function< SIG >& out )
	{
		typedef typename std::decay< TUPLE >::type TupleType;
		out = priv::TupleBinder< FUNC, TUPLE, SIG, 0 == std::tuple_size< TupleType >::value, std::tuple_size< TupleType >::value >::bindTuple( func, std::forward< TUPLE >( tuple ) );
	}
}

#endif // UTIL_BINDTUPLE_HPP
