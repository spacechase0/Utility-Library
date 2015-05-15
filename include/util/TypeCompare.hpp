#ifndef UTIL_TYPECOMPARE_HPP
#define UTIL_TYPECOMPARE_HPP

#include <typeinfo>

namespace util
{
	class TypeCompare
	{
		public:
			bool operator () ( const std::type_info* a, const std::type_info* b );
	};
}

#endif // UTIL_TYPECOMPARE_HPP
