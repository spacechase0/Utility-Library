# A lot of this (if not all) is taken from SFML's CMake files. :P

cmake_minimum_required( VERSION 2.8 )

# Build type
if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE )
endif()

# SFML
find_package( SFML )
if ( SFML_FOUND )
    include_directories( ${SFML_INCLUDE_DIR} )
else()
	message( FATAL_ERROR "We need SFML!" )
endif()

# Misc
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++0x" )

# Project
project( "Utility Library" )

set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )
set( VERSION_PATCH 0 )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Build
set( INCROOT ${PROJECT_SOURCE_DIR}/include )
set( SRCROOT ${PROJECT_SOURCE_DIR}/src )

set( INC ${INCROOT}/util/Base64.h
		 ${INCROOT}/util/Cache.h
		 ${INCROOT}/util/Cache.inl
		 ${INCROOT}/util/Convert.h
		 ${INCROOT}/util/Endian.h
		 ${INCROOT}/util/IniFile.h
		 ${INCROOT}/util/Math.h
		 ${INCROOT}/util/Md5.h
		 ${INCROOT}/util/Misc.h 
		 ${INCROOT}/util/Tokenize.h
		 ${INCROOT}/util/unsorted_map.h )

set( SRC ${SRCROOT}/util/Base64.cpp
		 ${SRCROOT}/util/Endian.cpp
		 ${SRCROOT}/util/File.cpp
		 ${SRCROOT}/util/IniFile.cpp
		 ${SRCROOT}/util/Md5.cpp
		 ${SRCROOT}/util/Tokenize.cpp )

add_library( sc0-utility SHARED ${SRC} ${INC} )
set_target_properties( sc0-utility PROPERTIES DEBUG_POSTFIX -d )

# Install
install( TARGETS sc0-utility
		 DESTINATION bin )
install( DIRECTORY include
		 DESTINATION . )
