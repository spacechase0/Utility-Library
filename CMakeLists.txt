# A lot of this (if not all) is taken from SFML's CMake files. :P

cmake_minimum_required( VERSION 2.8 )

# Build type
if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE )
endif()

# Project
project( "Utility Library" )

set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )
set( VERSION_PATCH 0 )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

# SFML
find_package( SFML )
if ( SFML_FOUND )
    include_directories( ${SFML_INCLUDE_DIR} )
else()
	message( FATAL_ERROR "We need SFML!" )
endif()

# Misc
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++0x" )

# Build
set( INCROOT ${PROJECT_SOURCE_DIR}/include )
set( SRCROOT ${PROJECT_SOURCE_DIR}/src )

set( INC ${INCROOT}/util/Base64.hpp
         ${INCROOT}/util/BindTuple.hpp
		 ${INCROOT}/util/Crc32.hpp
		 ${INCROOT}/util/Endian.hpp
		 ${INCROOT}/util/File.hpp
		 ${INCROOT}/util/FuncTraits.hpp
		 ${INCROOT}/util/GenericPlaceholder.hpp
		 ${INCROOT}/util/IniFile.hpp
		 ${INCROOT}/util/Logger.hpp
		 ${INCROOT}/util/Logger.inl
		 ${INCROOT}/util/Math.hpp
		 ${INCROOT}/util/Md5.hpp
		 ${INCROOT}/util/MemberFunctionProxy.hpp
		 ${INCROOT}/util/MemberObjectType.hpp
		 ${INCROOT}/util/Profiler.hpp
		 ${INCROOT}/util/StreamBufferPreserver.hpp
		 ${INCROOT}/util/String.hpp
		 ${INCROOT}/util/unsorted_map.hpp
		 ${INCROOT}/util/VersionManager.hpp
		 ${INCROOT}/util/VersionManager.inl )

set( SRC ${SRCROOT}/util/Base64.cpp
         ${SRCROOT}/util/Crc32.cpp
		 ${SRCROOT}/util/Endian.cpp
		 ${SRCROOT}/util/File.cpp
		 ${SRCROOT}/util/IniFile.cpp
		 ${SRCROOT}/util/Logger.cpp
		 ${SRCROOT}/util/Md5.cpp
		 ${SRCROOT}/util/String.cpp
		 ${SRCROOT}/util/StreamBufferPreserver.cpp )

add_library( sc0-utility SHARED ${SRC} ${INC} )
set_target_properties( sc0-utility PROPERTIES DEBUG_POSTFIX -d )

# Install
install( TARGETS sc0-utility
		 DESTINATION bin )
install( DIRECTORY include
		 DESTINATION . )
