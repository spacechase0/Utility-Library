#include <util/TypeCompare.hpp>

namespace util
{
	bool TypeCompare::operator () ( const std::type_info* a, const std::type_info* b )
	{
		return a->before( * b );
	}
}
