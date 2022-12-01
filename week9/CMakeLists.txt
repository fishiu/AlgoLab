cmake_minimum_required(VERSION 3.20)
project(week9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost COMPONENTS graph REQUIRED)

file (GLOB_RECURSE files solutions/*.cpp)
foreach (file ${files})
 string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
 add_executable (${exe} ${file})
 target_link_libraries(${exe} Boost::graph)
 message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
