cmake_minimum_required(VERSION 3.20)
project(week6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE debug)

find_package(CGAL)

file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
 string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
 add_executable (${exe} ${file})
 target_link_libraries(${exe} CGAL::CGAL)
 message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
