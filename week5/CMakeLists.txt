cmake_minimum_required(VERSION 3.20)
project(week5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE debug)

file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
 string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
 add_executable (${exe} ${file})
 message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
