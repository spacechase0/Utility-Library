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
