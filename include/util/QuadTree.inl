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
typename QuadTree< T, C >::CoordinatePair QuadTree< T, C >::GetPosition() const
{
	return myPos;
}

template< class T, typename C >
typename QuadTree< T, C >::CoordinatePair QuadTree< T, C >::GetSize() const
{
	return mySize;
}

template< class T, typename C >
bool QuadTree< T, C >::Contains( Coordinate x, Coordinate y ) const
{
	return Contains( CoordinatePair( x, y ) );
}

template< class T, typename C >
bool QuadTree< T, C >::Contains( CoordinatePair pos ) const
{
	if ( myPos.x <= pos.x and myPos.x + mySize.x > pos.x and 
		 myPos.y <= pos.y and myPos.y + mySize.y > pos.y )
	{
		return true;
	}
	
	return false;
}

template< class T, typename C >
void QuadTree< T, C >::Resize( Coordinate width, Coordinate height )
{
	Resize( CoordinatePair( width, height ) );
}

template< class T, typename C >
void QuadTree< T, C >::Resize( CoordinatePair size )
{
	mySize = size;
	
	CoordinatePair quarter( size.x / 2, size.y / 2 );
	
	if ( myIsSplit )
	{
		myQuadrants.topLeft->Resize( quarter );
		
		myQuadrants.topRight->myPos.x = myPos.x + quarter.x;
		myQuadrants.topRight->Resize( quarter );
		
		myQuadrants.bottomLeft->myPos.y = myPos.y + quarter.y;
		myQuadrants.bottomLeft->Resize( quarter );
		
		myQuadrants.bottomRight->myPos.x = myPos.x + quarter.x;
		myQuadrants.bottomRight->myPos.y = myPos.y + quarter.y;
		myQuadrants.bottomRight->Resize( quarter );
	}
}

template< class T, typename C >
QuadTree< T, C >* QuadTree< T, C >::GetQuadrant( Quadrant quadrant )
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
const QuadTree< T, C >* QuadTree< T, C >::GetQuadrant( Quadrant quadrant ) const
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
QuadTree< T, C >* QuadTree< T, C >::FindQuadrant( Coordinate x, Coordinate y )
{
	if ( myIsSplit )
	{
		if ( myQuadrants.topLeft->Contains( x, y ) )
		{
			return myQuadrants.topLeft;
		}
		else if ( myQuadrants.topRight->Contains( x, y ) )
		{
			return myQuadrants.topRight;
		}
		else if ( myQuadrants.bottomLeft->Contains( x, y ) )
		{
			return myQuadrants.bottomLeft;
		}
		else if ( myQuadrants.bottomRight->Contains( x, y ) )
		{
			return myQuadrants.bottomRight;
		}
		else if ( myParent != NULL )
		{
			return myParent->FindQuadrant( x, y );
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
		return myParent->FindQuadrant( x, y );
	}
	
	return NULL;
}

template< class T, typename C >
const QuadTree< T, C >* QuadTree< T, C >::FindQuadrant( Coordinate x, Coordinate y ) const
{
	if ( myIsSplit )
	{
		if ( myQuadrants.topLeft->Contains( x, y ) )
		{
			return myQuadrants.topLeft;
		}
		else if ( myQuadrants.topRight->Contains( x, y ) )
		{
			return myQuadrants.topRight;
		}
		else if ( myQuadrants.bottomLeft->Contains( x, y ) )
		{
			return myQuadrants.bottomLeft;
		}
		else if ( myQuadrants.bottomRight->Contains( x, y ) )
		{
			return myQuadrants.bottomRight;
		}
		else if ( myParent != NULL )
		{
			return myParent->FindQuadrant( x, y );
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
		return myParent->FindQuadrant( x, y );
	}
	
	return NULL;
}

template< class T, typename C >
bool QuadTree< T, C >::IsSplit() const
{
	return myIsSplit;
}

template< class T, typename C >
void QuadTree< T, C >::Split()
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->Split();
		myQuadrants.topRight->Split();
		myQuadrants.bottomLeft->Split();
		myQuadrants.bottomRight->Split();
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
			AddObject( * it );
		}
	}
	
	UpdateQuadrants();
}

template< class T, typename C >
void QuadTree< T, C >::Split( Quadrant quadrant )
{
	if ( !myIsSplit )
	{
		Split();
	}
	
	switch ( quadrant )
	{
		case TopLeft:     myQuadrants.topLeft->Split();
		case TopRight:    myQuadrants.topRight->Split();
		case BottomLeft:  myQuadrants.bottomLeft->Split();
		case BottomRight: myQuadrants.bottomRight->Split();
	}
}

template< class T, typename C >
void QuadTree< T, C >::Join()
{
	if ( !myIsSplit )
	{
		return;
	}
	
	#define DoJoin(a) \
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
		DoJoin( topLeft );
		DoJoin( topRight );
		DoJoin( bottomLeft );
		DoJoin( bottomRight );
		
		myIsSplit = false;
	}
	
	#undef DoJoin
}

template< class T, typename C >
void QuadTree< T, C >::AddObject( TypePtr object )
{
	if ( myIsSplit )
	{
		QuadTree< T, C >* tree = FindQuadrant( object->GetPosition().x, object->GetPosition().y );
		if ( tree != NULL )
		{
			tree->AddObject( object );
		}
	}
	else if ( myObjects.find( object ) == myObjects.end() )
	{
		myObjects.insert( object );
	}
}

template< class T, typename C >
void QuadTree< T, C >::RemoveObject( TypePtr object )
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->RemoveObject( object );
		myQuadrants.topRight->RemoveObject( object );
		myQuadrants.bottomLeft->RemoveObject( object );
		myQuadrants.bottomRight->RemoveObject( object );
	}
	else if ( myObjects.find( object ) != myObjects.end() )
	{
		myObjects.erase( object );
	}
}

template< class T, typename C >
auto QuadTree< T, C >::GetObjects() const -> const std::set< TypePtr >&
{
	return myObjects;
}

template< class T, typename C >
size_t QuadTree< T, C >::GetObjectCount() const
{
	if ( myIsSplit )
	{
		return myQuadrants.topLeft->GetObjectCount() + myQuadrants.topRight->GetObjectCount() + myQuadrants.bottomLeft->GetObjectCount() + myQuadrants.bottomRight->GetObjectCount();
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
		myQuadrants.topLeft->Update();
		myQuadrants.topRight->Update();
		myQuadrants.bottomLeft->Update();
		myQuadrants.bottomRight->Update();
	}
	else
	{
		for ( auto it = myObjects.begin(); it != myObjects.end(); ++it )
		{
			TypePtr ptr = ( * it );
			ptr->Update();
		}
	}
}

template< class T, typename C >
void QuadTree< T, C >::UpdateQuadrants()
{
	if ( myIsSplit )
	{
		myQuadrants.topLeft->UpdateQuadrants();
		myQuadrants.topRight->UpdateQuadrants();
		myQuadrants.bottomLeft->UpdateQuadrants();
		myQuadrants.bottomRight->UpdateQuadrants();
	}
	else if ( myParent != NULL )
	{
		for ( auto it = myObjects.begin(); it != myObjects.end(); ++it )
		{
			TypePtr ptr = ( * it );
			if ( !Contains( ptr->GetPosition() ) )
			{
				myObjects.erase( it );
				AddObject( ptr );
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
