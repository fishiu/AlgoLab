cmake_minimum_required(VERSION 3.20)
project(week7)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.79 COMPONENTS graph REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
 string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
 add_executable (${exe} ${file})
 target_link_libraries(${exe} Boost::graph)
 message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
