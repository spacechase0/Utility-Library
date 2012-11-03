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
	template < typename T >
	class FuncTraits;
	
	template< typename RET, typename... ARGS >
	class FuncTraits< RET ( ARGS... ) >
	{
		public:
			typedef RET Func( ARGS... );
			typedef Func* FuncPtr;
			
			typedef RET Return;
			
			typedef void Class;
			static constexpr bool ClassConst = false;
			
			static constexpr int ArgCount = sizeof...( ARGS );
			typedef std::tuple< ARGS... > ArgTuple;
			
			template< int NUM >
			class Arg
			{
				public:
					typedef typename std::tuple_element< NUM, std::tuple< ARGS... > >::type Type;
			};
	};
	
	template< typename RET, typename... ARGS >
	class FuncTraits< RET ( * ) ( ARGS... ) > : public FuncTraits< RET ( ARGS... ) >
	{
	};

	template< class CLASS, typename RET, typename... ARGS >
	class FuncTraits< RET ( CLASS::* ) ( ARGS... ) > : public FuncTraits< RET ( CLASS*, ARGS... ) >
	{
		public:
			typedef CLASS Class;
			static constexpr bool ClassConst = false;
			
			// Normal = before we added the class parameter
			
			typedef RET NormalFunc( ARGS... );
			typedef NormalFunc* NormalFuncPtr;
			
			static constexpr int NormalArgCount = sizeof...( ARGS );
			typedef std::tuple< ARGS... > NormalArgTuple;
			
			template< int NUM >
			class NormalArg
			{
				public:
					typedef typename std::tuple_element< NUM, std::tuple< ARGS... > >::type Type;
			};
	};

	template< class CLASS, typename RET, typename... ARGS >
	class FuncTraits< RET ( CLASS::* ) ( ARGS... ) const > : public FuncTraits< RET ( const CLASS*, ARGS... ) >
	{
		public:
			typedef const CLASS Class;
			static constexpr bool ClassConst = true;
			
			// Normal = before we added the class parameter
			
			typedef RET NormalFunc( ARGS... );
			typedef NormalFunc* NormalFuncPtr;
			
			static constexpr int NormalArgCount = sizeof...( ARGS );
			typedef std::tuple< ARGS... > NormalArgTuple;
			
			template< int NUM >
			class NormalArg
			{
				public:
					typedef typename std::tuple_element< NUM, std::tuple< ARGS... > >::type Type;
			};
	};
}

#endif // UTIL_FUNCTRAITS_HPP
