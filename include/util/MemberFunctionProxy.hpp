#ifndef UTIL_MEMBERFUNCTIONPROXY_HPP
#define UTIL_MEMBERFUNCTIONPROXY_HPP

#include <tuple>

#include "util/FuncTraits.hpp"

namespace util
{
	// NOTE: A lot of this next section (minus memberFunctionProxy itself) was modified from here:
	// http://stackoverflow.com/questions/10766112/c11-i-can-go-from-multiple-args-to-tuple-but-can-i-go-from-tuple-to-multiple
	// Just like stuff for bindTuple()
	namespace priv
	{
		// This is really confusing, I think I'll comment this for once :P
		/**
		 * Used to get a plain function pointer from a member function pointer.
		 * Like this (at least with no parameters):
		 *
		 * auto func = &memberFunctionProxy< MyClass, decltype( &MyClass::func ), &MyClass::func >;
		 *
		 * Currently, I want to try to find a way to not have to put the reference twice. I'm not
		 * sure if that's possible though, since constexpr functions have to also be compiled for
		 * runtime usage (like. you can't using parameters in templates).
		 **/
		template< typename CLASSPTR, typename PTRTYPE, PTRTYPE PTR, typename... ARGS >
		typename util::FuncTraits< PTRTYPE >::Return memberFunctionProxy( CLASSPTR that, ARGS&&... args )
		{
			static_assert( std::is_same< typename util::FuncTraits< PTRTYPE >::FuncPtr, decltype( &memberFunctionProxy< CLASSPTR, PTRTYPE, PTR, ARGS... > ) >::value, "Incompatible?" );
			// Can't add a space before the '*'? Weird
			return ( that->* PTR )( std::forward< ARGS >( args )... );
		}
		
		template< typename FUNCPTR, FUNCPTR FUNC, typename TUPLE, bool DONE, int MAX, int... N >
		struct MemberFunctionProxy
		{
			typedef typename util::FuncTraits< FUNCPTR > Traits;
			
			static typename Traits::FuncPtr makeMemberFunctionProxy()
			{
				return MemberFunctionProxy< FUNCPTR, FUNC, TUPLE, MAX == ( 1 + sizeof...( N ) ), MAX, N..., sizeof...( N ) >::makeMemberFunctionProxy();
			}
		};
		
		template< typename FUNCPTR, FUNCPTR FUNC, typename TUPLE, int MAX, int... N >
		struct MemberFunctionProxy< FUNCPTR, FUNC, TUPLE, true, MAX, N... >
		{
			typedef typename util::FuncTraits< FUNCPTR > Traits;
			
			static typename Traits::FuncPtr makeMemberFunctionProxy()
			{
				return &memberFunctionProxy< typename Traits::template Arg< 0 >::Type, FUNCPTR, FUNC, typename std::tuple_element< N, TUPLE >::type... >;
			}
		};
	}

	template< typename FUNCPTR, FUNCPTR FUNC >
	typename util::FuncTraits< FUNCPTR >::FuncPtr makeMemberFunctionProxy()
	{
		typedef typename util::FuncTraits< FUNCPTR >::NormalArgTuple TUPLE;
		typedef typename std::decay< TUPLE >::type TupleType;
		return priv::MemberFunctionProxy< FUNCPTR, FUNC, TUPLE, 0 == std::tuple_size< TupleType >::value, std::tuple_size< TupleType >::value >::makeMemberFunctionProxy();
	}
}

#endif // UTIL_MEMBERFUNCTIONPROXY_HPP
