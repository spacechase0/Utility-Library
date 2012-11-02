#ifndef UTIL_MEMBERFUNCTIONPROXY_HPP
#define UTIL_MEMBERFUNCTIONPROXY_HPP

namespace util
{
	// TO DO: Is it possible to read args from util::FuncTraits::Arg<...> as well?
	// I kinda doubt it
	
	// This is really confusing, I think I'll comment this for once :P
	/**
	 * Used to get a plain function pointer from a member function pointer.
	 * Like this (at least with no parameters):
	 *
	 * auto func = &memberFunctionProxy< MyClass, decltype( &MyClass::func ), &MyClass::func >;
	 *
	 * Currently, I want to try to find a way to not have to specify the argument types (by
	 * deducing it from the pointer type), and not having to put the reference twice. If
	 * possible, they'll most likely be done via a makeMemberFunctionProxy(), or something
	 * like that.
	 **/
	template< typename CLASS, typename PTRTYPE, PTRTYPE PTR, typename... ARGS >
	typename util::FuncTraits< PTRTYPE >::Return memberFunctionProxy( CLASS* that, ARGS&&... args )
	{
		// Can't add a space before the '*'? Weird
		return ( that->* PTR )( std::forward< ARGS >( args )... );
	}
}

#endif // UTIL_MEMBERFUNCTIONPROXY_HPP
