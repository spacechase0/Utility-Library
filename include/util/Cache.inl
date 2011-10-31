////////////////////////////////////////////////////////////
//
// Utility Library
// Copyright (C) 2011 Chase Warrington (staff@spacechase0.com)
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

template < class T >
Cache< T >::Cache()
   : cached(),
     isValid( false )
{
}

template < class T >
Cache< T >::Cache( T theCached )
   : cached( theCached ),
     isValid( true )
{
}

template < class T >
T& Cache< T >::Get()
{
	return cached;
}

template < class T >
const T& Cache< T >::Get() const
{
	return cached;
}

template < class T >
Cache< T >::operator T&()
{
	return cached;
}

template < class T >
Cache< T >::operator const T&() const
{
	return cached;
}

template < class T >
void Cache< T >::Set( const T& theCached )
{
	cached = theCached;
	isValid = true;
}

template < class T >
Cache< T >& Cache< T >::operator =( const T& theCached )
{
	cached = theCached;
	isValid = true;
}

template < class T >
bool Cache< T >::IsValid() const
{
	return isValid;
}

template < class T >
Cache< T >::operator bool() const
{
	return isValid;
}

template < class T >
void Cache< T >::Invalidate()
{
	isValid = false;
}
