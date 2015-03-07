#ifndef UTIL_GENERICPLACEHOLDER_HPP
#define UTIL_GENERICPLACEHOLDER_HPP

#include <functional>
#include <tuple>

// TO DO: Separate into two files

namespace util
{
	template< int N >
	struct GenericPlaceholder
	{
	};
	
	namespace priv
	{
		template< int N >
		struct GenericPlaceholderBuilder;

		template<>
		struct GenericPlaceholderBuilder< 1 >
		{
			static std::tuple< GenericPlaceholder< 1 > > getTuple()
			{
				return std::tuple< GenericPlaceholder< 1 > >();
			}
		};
		
		template< int N >
		struct GenericPlaceholderBuilder
		{
			typedef GenericPlaceholder< N > ThisArg;
			typedef GenericPlaceholderBuilder< N - 1 > PreviousTuple;
			static auto getTuple() -> decltype( std::tuple_cat( PreviousTuple::getTuple(), std::make_tuple( ThisArg() ) ) )
			{
				return std::tuple_cat( PreviousTuple::getTuple(), std::make_tuple( ThisArg() ) );
			}
		};
	}
	
	template< int N >
	auto getPlaceholders() -> decltype( priv::GenericPlaceholderBuilder< N >::getTuple() )
	{
		return priv::GenericPlaceholderBuilder< N >::getTuple();
	}
}

namespace std
{
	template< int N >
	struct is_placeholder< util::GenericPlaceholder< N > > : std::integral_constant< int, N >
	{
	};
}

#endif // UTIL_GENERICPLACEHOLDER_HPP
