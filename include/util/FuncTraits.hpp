#ifndef UTIL_FUNCTRAITS_HPP
#define UTIL_FUNCTRAITS_HPP

namespace util
{
	// Based on http://stackoverflow.com/questions/7943525/is-it-possible-to-figure-out-the-parameter-type-and-return-type-of-a-lambda
	// Had to play with it some to get it working. :P The main thing
	// I found out was that you have to do this:
	// 	typename FuncTraits< ... >::template Arg< ... >::Type
	// Instead of:
	// 	FuncTraits< ... >::Arg< ... >::Type
	// Or at least, that's how my version of GCC acts
	template< typename RET, typename... ARGS >
	class FuncTraits
	{
		public:
			typedef RET Func( ARGS... );
			typedef Func* FuncPtr;
			
			typedef RET Return;
			
			static constexpr int ArgCount = sizeof...( ARGS );
			
			template< int NUM >
			class Arg
			{
				public:
					typedef typename std::tuple_element< NUM, std::tuple< ARGS... > >::type Type;
			};
	};

	template< typename RET, typename... ARGS >
	class FuncTraits< RET ( ARGS... ) > : public FuncTraits< RET, ARGS... >
	{
	};

	template< typename RET, typename... ARGS >
	class FuncTraits< RET (*) ( ARGS... ) > : public FuncTraits< RET ( ARGS... ) >
	{
	};
}

#endif // UTIL_FUNCTRAITS_HPP
