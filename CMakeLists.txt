cmake_minimum_required(VERSION 3.16)
project(generating_thrift_files_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# C++ #
set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

set(COMMON_LIBS ${COMMON_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Boost #
find_package(Boost REQUIRED COMPONENTS system thread)

if (Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else ()
    message(WARNING "Boost not found")
endif ()

set(COMMON_LIBS ${Boost_LIBRARIES})

# Thrift #
find_package(Thrift REQUIRED)

option(THRIFT_LIBRARIES_REQUIRED "Project initialization should fail on missed thrift libraries" ON)

find_path(THRIFT_INCLUDE_DIR
    NAMES thrift/Thrift.h
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES include
)

find_library(THRIFT_LIBRARY
    thrift
    HINTS ${THRIFT_ROOT}
    PATH_SUFFIXES lib
)

include_directories(SYSTEM ${THRIFT_INCLUDE_DIR})
if (THRIFT_LIBRARY)
    set(COMMON_LIBS ${COMMON_LIBS} ${THRIFT_LIBRARY})
endif ()

# includes #
add_subdirectory(calculator_server)
add_subdirectory(calculator_client)