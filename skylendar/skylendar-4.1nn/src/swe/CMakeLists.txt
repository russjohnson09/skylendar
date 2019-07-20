INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(swelib_SRCS
swecl.c    swehouse.c  swemmoon.c  swepdate.c  swephlib.c
swedate.c  swejpl.c    swemplan.c  swepcalc.c  sweph.c swehel.c
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	add_definitions(-fPIC)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

add_library(swe STATIC ${swelib_SRCS})
target_link_libraries(swe dl m)

########### install files ###############

