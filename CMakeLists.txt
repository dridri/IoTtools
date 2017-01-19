cmake_minimum_required( VERSION 2.6 )
project( iottools )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g3 -std=c11 -D_GNU_SOURCE -D_BSD_SOURCE" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g3 -std=c++11 -fpermissive -Wno-pmf-conversions" )


include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/links )

add_library( iottools STATIC
			 Debug.cpp
			 Messenger.cpp
			 links/Link.cpp
			 links/Socket.cpp
			)
target_link_libraries( iottools )

add_executable( example-01-basic examples/01-basic.cpp )
target_link_libraries( example-01-basic iottools -pthread )
