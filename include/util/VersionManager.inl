namespace util
{
	template < typename T >
	void VersionManager< T >::addVersion( T t )
	{
		versions.push_back( t );
	}

	template < typename T >
	T VersionManager< T >::getVersion( std::size_t version ) const
	{
		return versions[ version ];
	}

	template < typename T >
	std::size_t VersionManager< T >::getVersionCount() const
	{
		return versions.size();
	}
}
