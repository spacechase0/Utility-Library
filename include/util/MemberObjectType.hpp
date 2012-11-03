#ifndef UTIL_MEMBEROBJECTTYPE_HPP
#define UTIL_MEMBEROBJECTTYPE_HPP

namespace util
{
	template< typename... ARGS >
	class MemberObjectType;
	
	template< class CLASS, typename TYPE >
	class MemberObjectType< TYPE CLASS::* >
	{
		public:
			typedef CLASS Class;
			typedef TYPE Type;
	};
}

#endif // UTIL_MEMBEROBJECTTYPE_HPP
