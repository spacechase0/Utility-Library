#ifndef UTIL_VERSIONMANAGER_HPP
#define UTIL_VERSIONMANAGER_HPP

#include <array>

namespace util
{
	// TO DO: Bring in util::Registry from my other project, and make this based on that,
	// with a few more functions
	template < typename T >
	class VersionManager
	{
		public:
			void addVersion( T t );
			T getVersion( std::size_t version ) const;
			std::size_t getVersionCount() const;
		
		private:
			std::vector< T > versions;
	};
}

#include <util/VersionManager.inl>

#endif // UTIL_VERSIONMANAGER_HPP
