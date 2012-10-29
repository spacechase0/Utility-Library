////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

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
