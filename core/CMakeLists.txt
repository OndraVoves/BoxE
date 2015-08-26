###################
# CMake settings. #
###################
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
SET( CMAKE_VERBOSE_MAKEFILE ON )
SET( CMAKE_COLOR_MAKEFILE ON )

#####################
# Project settings. #
#####################
PROJECT( BoxE )

OPTION( BOXE_DEBUG "Build BoxE in debug mode" ON )
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Check debug mode.
IF( BOXE_DEBUG )
    SET( CFLAGS ${CFLAGS} " -Wunused-parameter -W -Wall -ansi -pedantic -O0 -g " )
ELSE( BOXE_DEBUG )
    SET( CFLAGS ${CFLAGS} " -W -Wall -ansi -pedantic" )
ENDIF( BOXE_DEBUG )


#########################
# Find and set library. #
#########################

if( ${UNIX} )
  set( LIBS ${LIBS} "-ldl" )
endif()

####################
# Set sourcefiles. #
####################
file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


SET_PROPERTY( SOURCE ${SRCS} APPEND PROPERTY COMPILE_FLAGS ${CFLAGS} )

ADD_LIBRARY( boxe-core SHARED ${SRCS} )
TARGET_LINK_LIBRARIES( boxe-core ${LIBS} )
