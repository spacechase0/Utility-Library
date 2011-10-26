#ifndef UTIL_CACHE_H
#define UTIL_CACHE_H

namespace util
{
	template < class T >
	class Cache
	{
		public:
			Cache();
			Cache( T theCached );
			
			T& Get();
			const T& Get() const;
			operator T&();
			operator const T&() const;
			
			void Set( const T& theCached );
			Cache< T >& operator =( const T& theCached );
			
			bool IsValid() const;
			operator bool() const;
			void Invalidate();
		
		protected:
			T cached;
			bool isValid;
	};
	
	#include "util/Cache.inl"
}

#endif // UTIL_CACHE_H
