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

#ifndef UTIL_QUADTREE_HPP
#define UTIL_QUADTREE_HPP

#include <SFML/System.hpp>
#include <memory>
#include <set>

namespace util
{
	template< class T, typename C = float >
	class QuadTree
	{
		public:
			typedef T Type;
			typedef std::shared_ptr< T > TypePtr;
			
			typedef C Coordinate;
			typedef sf::Vector2< C > CoordinatePair;
			
			QuadTree();
			QuadTree( Coordinate width, Coordinate height );
			QuadTree( CoordinatePair size );
			// TO DO: Copy, assignment, move(?)
			~QuadTree();
			
			CoordinatePair getPosition() const;
			CoordinatePair getSize() const;
			bool contains( Coordinate x, Coordinate y ) const;
			bool contains( CoordinatePair pos ) const;
			void resize( Coordinate width, Coordinate height );
			void resize( CoordinatePair size );
			
			enum Quadrant : sf::Uint8
			{
				TopLeft,
				TopRight,
				BottomLeft,
				BottomRight,
			};
			
			QuadTree< T, C >* getQuadrant( Quadrant quadrant );
			QuadTree< T, C >* findQuadrant( Coordinate x, Coordinate y );
			const QuadTree< T, C >* getQuadrant( Quadrant quadrant ) const;
			const QuadTree< T, C >* findQuadrant( Coordinate x, Coordinate y ) const;
			
			bool isSplit() const;
			void split();
			void split( Quadrant quadrant );
			void join();
			
			void addObject( TypePtr object );
			void removeObject( TypePtr object );
			const std::set< TypePtr >& getObjects() const;
			size_t getObjectCount() const;
			
			void update();
			void updateQuadrants();
			
		private:
			QuadTree( QuadTree* parent );
			
			QuadTree* myParent;
			CoordinatePair myPos;
			CoordinatePair mySize;
			
			bool myIsSplit;
			std::set< TypePtr > myObjects;
			struct
			{
				QuadTree< T, C >* topLeft;
				QuadTree< T, C >* topRight;
				QuadTree< T, C >* bottomLeft;
				QuadTree< T, C >* bottomRight;
			} myQuadrants;
	};
}

#include "util/QuadTree.inl"

#endif // UTIL_QUADTREE_HPP
