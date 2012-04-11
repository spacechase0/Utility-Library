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

template< class T, typename C >
QuadTree< T, C >::QuadTree()
   : myParent( NULL ),
	 myPos( 0, 0 ),
	 mySize( 0, 0 ),
	 myIsSplit( false ),
	 myQuadrants{ NULL, NULL, NULL, NULL }
{
}

template< class T, typename C >
QuadTree< T, C >::QuadTree( Coordinate width, Coordinate height )
   : myParent( NULL ),
	 myPos( 0, 0 ),
	 mySize( 0, 0 ),
	 myIsSplit( false ),
	 myQuadrants{ NULL, NULL, NULL, NULL }
{
	Resize( width, height );
}

template< class T, typename C >
QuadTree< T, C >::QuadTree( CoordinatePair size )
   : myParent( NULL ),
	 myPos( 0, 0 ),
	 mySize( 0, 0 ),
	 myIsSplit( false ),
	 myQuadrants{ NULL, NULL, NULL, NULL }
{
	Resize( size );
}

template< class T, typename C >
QuadTree< T, C >::~QuadTree()
{
	if ( myIsSplit )
	{
		delete myQuadrants.topLeft;
		delete myQuadrants.topRight;
		delete myQuadrants.bottomLeft;
		delete myQuadrants.bottomRight;
	}
}

template< class T, typename C >
typename QuadTree< T, C >::CoordinatePair QuadTree< T, C >::getPosition() const
{
	return myPos;
}

template< class T, typename C >
typename QuadTree< T, C >::CoordinatePair QuadTree< T, C >::getSize() const
{
	return mySize;
}

template< class T, typename C >
bool QuadTree< T, C >::contains( Coordinate x, Coordinate y ) const
{
	return contains( CoordinatePair( x, y ) );
}

template< class T, typename C >
bool QuadTree< T, C >::contains( CoordinatePair pos ) const
{
	if ( myPos.x <= pos.x and myPos.x + mySize.x > pos.x and 
		 myPos.y <= pos.y and myPos.y + mySize.y > pos.y )
	{
		return true;
	}
	
	return false;
}

template< class T, typename C >
void QuadTree< T, C >::resize( Coordinate width, Coordinate height )
{
	Resize( CoordinatePair( width, height ) );
}

template< class T, typename C >
void QuadTree< T, C >::resize( CoordinatePair size )
{
	mySize = size;
	
	CoordinatePair quarter( size.x / 2, size.y / 2 );
	
	if ( myIsSplit )
	{
		myQuadrants.topLeft->resize( quarter );
		
		myQuadrants.topRight->myPos.x = myPos.x + quarter.x;
		myQuadrants.topRight->resize( quarter );
		
		myQuadrants.bottomLeft->myPos.y = myPos.y + quarter.y;
		myQuadrants.bottomLeft->resize( quarter );
		
		myQuadrants.bottomRight->myPos.x = myPos.x + quarter.x;
		myQuadrants.bottomRight->myPos.y = myPos.y + quarter.y;
		myQuadrants.bottomRight->resize( quarter );
	}
}

template< class T, typename C >
QuadTree< T, C >* QuadTree< T, C >::getQuadrant( Quadrant quadrant )
{
	switch ( quadrant )
	{
		case TopLeft:     return myQuadrants.topLeft;
		case TopRight:    return myQuadrants.topRight;
		case BottomLeft:  return myQuadrants.bottomLeft;
		case BottomRight: return myQuadrants.bottomRight;
	}
	
	return NULL;
}

template< class T, typename C >
const QuadTree< T, C >* QuadTree< T, C >::getQuadrant( Quadrant quadrant ) const
{
	switch ( quadrant )
	{
		case TopLeft:     return myQuadrants.topLeft;
		case TopRight:    return myQuadrants.topRight;
		case BottomLeft:  return myQuadrants.bottomLeft;
		case BottomRight: return myQuadrants.bottomRight;
	}
	
	return NULL;
}

template< class T, typename C >
QuadTree< T, C >* QuadTree< T, C >::findQuadrant( Coordinate x, Coordinate y )
{
	if ( myIsSplit )
	{
		if ( myQuadrants.topLeft->contains( x, y ) )
		{
			return myQuadrants.topLeft;
		}
		else if ( myQuadrants.topRight->contains( x, y ) )
		{
			return myQuadrants.topRight;
		}
		else if ( myQuadrants.bottomLeft->contains( x, y ) )
		{
			return myQuadrants.bottomLeft;
		}
		else if ( myQuadrants.bottomRight->contains( x, y ) )
		{
			return myQuadrants.bottomRight;
		}
		else if ( myParent != NULL )
		{
			return myParent->findQuadrant( x, y );
		}
		
		return NULL;
	}
	else if ( x >= myPos.x and x < myPos.x + mySize.x and
			  y >= myPos.y and y < myPos.y + mySize.y )
	{
		return this;
	}
	else if ( myParent != NULL )
	{
		return myParent->findQuadrant( x, y );
	}
	
	return NULL;
}

template< class T, typename C >
const QuadTree< T, C >* QuadTree< T, C >::findQuadrant( Coordinate x, Coordinate y ) const
{
	if ( myIsSplit )
	{
		if ( myQuadrants.topLeft->contains( x, y ) )
		{
			return myQuadrants.topLeft;
		}
		else if ( myQuadrants.topRight->contains( x, y ) )
		{
			return myQuadrants.topRight;
		}
		else if ( myQuadrants.bottomLeft->contains( x, y ) )
		{
			return myQuadrants.bottomLeft;
		}
		else if ( myQuadrants.bottomRight->contains( x, y ) )
		{
			return myQuadrants.bottomRight;
		}
		else if ( myParent != NULL )
		{
			return myParent->findQuadrant( x, y );
		}
		
		return NULL;
	}
	else if ( x >= myPos.x and x < myPos.x + mySize.x and
			  y >= myPos.y and y < myPos.y + mySize.y )
	{
		return this;
	}
	else if ( myParent != NULL )
	{
		return myParent->findQuadrant( x, y );
	}
	
	return NULL;
}

template< class T, typename C >
bool QuadTree< T, C >::isSplit() const
{
	return myIsSplit;
}

template< class T, typename C >
void QuadTree< T, C >::split()
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->split();
		myQuadrants.topRight->split();
		myQuadrants.bottomLeft->split();
		myQuadrants.bottomRight->split();
	}
	else
	{
		myQuadrants.topLeft = new QuadTree< T, C >( this );
		myQuadrants.topLeft->myPos = myPos;
		myQuadrants.topLeft->mySize = CoordinatePair( mySize.x / 2, mySize.y / 2 );
		
		myQuadrants.topRight = new QuadTree< T, C >( this );
		myQuadrants.topRight->myPos = CoordinatePair( myPos.x + mySize.x / 2, myPos.y );
		myQuadrants.topRight->mySize = CoordinatePair( mySize.x / 2, mySize.y / 2 );
		
		myQuadrants.bottomLeft = new QuadTree< T, C >( this );
		myQuadrants.bottomLeft->myPos = CoordinatePair( myPos.x, myPos.y + mySize.y / 2 );
		myQuadrants.bottomLeft->mySize = CoordinatePair( mySize.x / 2, mySize.y / 2 );
		
		myQuadrants.bottomRight = new QuadTree< T, C >( this );
		myQuadrants.bottomRight->myPos = CoordinatePair( myPos.x + mySize.x / 2, myPos.y + mySize.y / 2);
		myQuadrants.bottomRight->mySize = CoordinatePair( mySize.x / 2, mySize.y / 2 );
		
		myIsSplit = true;
		
		auto objects = myObjects;
		myObjects.clear();
		for ( auto it = objects.begin(); it != objects.end(); ++it )
		{
			addObject( * it );
		}
	}
	
	updateQuadrants();
}

template< class T, typename C >
void QuadTree< T, C >::split( Quadrant quadrant )
{
	if ( !myIsSplit )
	{
		Split();
	}
	
	switch ( quadrant )
	{
		case TopLeft:     myQuadrants.topLeft->split();
		case TopRight:    myQuadrants.topRight->split();
		case BottomLeft:  myQuadrants.bottomLeft->split();
		case BottomRight: myQuadrants.bottomRight->split();
	}
}

template< class T, typename C >
void QuadTree< T, C >::join()
{
	if ( !myIsSplit )
	{
		return;
	}
	
	#define doJoin(a) \
		myObjects.insert( myQuadrants.a->myObjects.begin(), myQuadrants.a->myObjects.end() ); \
		myQuadrants.a->myObjects.clear(); \
		delete myQuadrants.a; \
		myQuadrants.a = NULL \
	
	if ( myQuadrants.topLeft->myIsSplit or myQuadrants.topRight->myIsSplit or myQuadrants.bottomLeft->myIsSplit or myQuadrants.bottomRight->myIsSplit )
	{
		myQuadrants.topLeft->Join();
		myQuadrants.topRight->Join();
		myQuadrants.bottomLeft->Join();
		myQuadrants.bottomRight->Join();
	}
	else
	{
		doJoin( topLeft );
		doJoin( topRight );
		doJoin( bottomLeft );
		doJoin( bottomRight );
		
		myIsSplit = false;
	}
	
	#undef DoJoin
}

template< class T, typename C >
void QuadTree< T, C >::addObject( TypePtr object )
{
	if ( myIsSplit )
	{
		QuadTree< T, C >* tree = findQuadrant( object->getPosition().x, object->getPosition().y );
		if ( tree != NULL )
		{
			tree->addObject( object );
		}
	}
	else if ( myObjects.find( object ) == myObjects.end() )
	{
		myObjects.insert( object );
	}
}

template< class T, typename C >
void QuadTree< T, C >::removeObject( TypePtr object )
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->removeObject( object );
		myQuadrants.topRight->removeObject( object );
		myQuadrants.bottomLeft->removeObject( object );
		myQuadrants.bottomRight->removeObject( object );
	}
	else if ( myObjects.find( object ) != myObjects.end() )
	{
		myObjects.erase( object );
	}
}

template< class T, typename C >
auto QuadTree< T, C >::getObjects() const -> const std::set< TypePtr >&
{
	return myObjects;
}

template< class T, typename C >
size_t QuadTree< T, C >::getObjectCount() const
{
	if ( myIsSplit )
	{
		return myQuadrants.topLeft->getObjectCount() + myQuadrants.topRight->getObjectCount() + myQuadrants.bottomLeft->getObjectCount() + myQuadrants.bottomRight->getObjectCount();
	}
	else
	{
		return myObjects.size();
	}
}

template< class T, typename C >
void QuadTree< T, C >::Update()
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->update();
		myQuadrants.topRight->update();
		myQuadrants.bottomLeft->update();
		myQuadrants.bottomRight->update();
	}
	else
	{
		for ( auto it = myObjects.begin(); it != myObjects.end(); ++it )
		{
			TypePtr ptr = ( * it );
			ptr->update();
		}
	}
}

template< class T, typename C >
void QuadTree< T, C >::updateQuadrants()
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->updateQuadrants();
		myQuadrants.topRight->updateQuadrants();
		myQuadrants.bottomLeft->updateQuadrants();
		myQuadrants.bottomRight->updateQuadrants();
	}
	else if ( myParent != NULL )
	{
		for ( auto it = myObjects.begin(); it != myObjects.end(); ++it )
		{
			TypePtr ptr = ( * it );
			if ( !contains( ptr->getPosition() ) )
			{
				myObjects.erase( it );
				addObject( ptr );
				it = myObjects.find( ptr );
			}
		}
	}
}
/*
template< class T, typename C >
QuadTree< T, C >::

template< class T, typename C >
QuadTree< T, C >::

template< class T, typename C >
QuadTree< T, C >::

template< class T, typename C >
QuadTree< T, C >::

template< class T, typename C >
QuadTree< T, C >::
//*/

template< class T, typename C >
QuadTree< T, C >::QuadTree( QuadTree< T, C >* parent )
   : myParent( parent ),
	 myPos( 0, 0 ),
	 mySize( 0, 0 ),
	 myIsSplit( false ),
	 myQuadrants{ NULL, NULL, NULL, NULL }
{
}
