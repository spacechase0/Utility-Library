////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2013 Chase Warrington (staff@spacechase0.com)
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

#ifndef UTIL_UNSORTED_MAP_HPP
#define UTIL_UNSORTED_MAP_HPP

#include <utility>
#include <vector>

namespace util
{
	// TO DO: Make this the interface of a map, NOT a vector :P
	template< class TK, class TV, class Allocator = std::allocator< std::pair< TK, TV > > >
	class unsorted_map
	{
		public:
			typedef TK key_type;   // Mine
			typedef TV value_type; // Modified
			typedef std::pair< TK, TV > pair_type; // Mine
			
			typedef typename std::vector< pair_type >::reference reference;
			typedef typename std::vector< pair_type >::const_reference const_reference;
			typedef typename std::vector< pair_type >::iterator iterator;
			typedef typename std::vector< pair_type >::const_iterator const_iterator;
			typedef typename std::vector< pair_type >::size_type size_type;
			typedef typename std::vector< pair_type >::difference_type difference_type;
			typedef typename std::vector< pair_type >::allocator_type allocator_type;
			typedef typename std::vector< pair_type >::pointer pointer;
			typedef typename std::vector< pair_type >::const_pointer const_pointer;
			typedef typename std::vector< pair_type >::reverse_iterator reverse_iterator;
			typedef typename std::vector< pair_type >::const_reverse_iterator const_reverse_iterator;
			
			explicit unsorted_map( const Allocator& allocator = Allocator() ) : vec( allocator ) {};
			explicit unsorted_map( size_type n, const pair_type& value = pair_type(), const Allocator& allocator = Allocator() ) : vec( n, value, allocator ) {}
			template< class InputIterator >
			unsorted_map( InputIterator first, InputIterator last, const Allocator& allocator = Allocator() ) : vec( first, last, allocator ) {}
			unsorted_map( const unsorted_map& x ) : vec( x.vec ) {}
			~unsorted_map() {}
			unsorted_map& operator = ( const unsorted_map& x ) { vec = x.vec; return ( * this ); }
			
			iterator begin() { return vec.begin(); }
			const_iterator begin() const { return vec.begin(); }
			iterator end() { return vec.end(); }
			const_iterator end() const { return vec.end(); }
			reverse_iterator rbegin() { return vec.rbegin(); }
			const_reverse_iterator rbegin() const { return vec.rbegin(); }
			reverse_iterator rend() { return vec.rend(); }
			const_reverse_iterator rend() const { return vec.rend(); }
			
			size_type size() const { return vec.size(); }
			size_type max_size() const { return vec.max_size(); }
			void resize( size_type sz, pair_type c = pair_type() ) { vec.resize( sz, c ); }
			size_type capacity() const { return vec.capacity(); }
			bool empty() const { return vec.empty(); }
			void reserve( size_type n ) { vec.resize( n ); }
			
			reference operator [] ( size_type n ) { return vec[ n ]; };
			const_reference operator [] ( size_type n ) const { return vec[ n ] ;}
			reference at( size_type n ) { return vec.at( n ); }
			const_reference at( size_type n ) const { return vec.at( n ); }
			reference front() { return vec.front(); }
			const_reference front() const { return vec.front(); }
			reference back() { return vec.back(); }
			const_reference back() const { return vec.back(); }
			
			template< class InputIterator >
			void assign( InputIterator first, InputIterator last ) { vec.assign( first, last ); }
			void assign( size_type n, const pair_type& u ) { vec.assign( n, u ); }
			void push_back( const pair_type& x ) { vec.push_back( x ); }
			void pop_back() { vec.pop_back(); }
			iterator insert( iterator position, const pair_type& x ) { return vec.insert( position, x ); }
			void insert( iterator position, size_type n, const pair_type& x ) { vec.insert( position, n, x ); }
			template< class InputIterator >
			void insert( iterator position, InputIterator first, InputIterator last ) { vec.insert( position, first, last ); }
			iterator erase( iterator position ) { return vec.erase( position ); }
			iterator erase( iterator first, iterator last ) { return vec.erase( first, last ); }
			void swap( unsorted_map& map ) { vec.swap( map.vec ); }
			void clear() { vec.clear(); }
			
			allocator_type get_allocator() const { return vec.get_allocator(); }
			
			// Mine
			iterator find( const key_type& key )
			{
				for ( auto it = vec.begin(); it != vec.end(); ++it )
				{
					if ( it->first == key )
					{
						return it;
					}
				}
				
				return end();
			}
			
			const_iterator find( const key_type& key ) const
			{
				for ( auto it = vec.begin(); it != vec.end(); ++it )
				{
					if ( it->first == key )
					{
						return it;
					}
				}
				
				return end();
			}
			
			value_type& operator [] ( const key_type& key )
			{
				return find( key )->second;
			}
			
			const value_type& operator [] ( const key_type& key ) const
			{
				return find( key )->second;
			}
			
			value_type& at ( const key_type& key )
			{
				return find( key )->second;
			}
			
			const value_type& at ( const key_type& key ) const
			{
				return find( key )->second;
			}
			
		private:
			std::vector< pair_type, Allocator > vec;
	};
}

#endif // UTIL_UNSORTED_MAP_HPP
