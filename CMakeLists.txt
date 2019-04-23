cmake_minimum_required(VERSION 3.9)
project(KomischesPlottingDings)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(KomischesPlottingDings main.cpp Output/BmpWriter.cpp Output/BmpWriter.hpp Render3d.cpp Render3d.hpp Point3d.cpp Point3d.hpp Output/ImageWriter.hpp Output/XWriter.cpp Output/XWriter.hpp Plot.cpp Plot.hpp Pcd.cpp)
target_link_libraries(KomischesPlottingDings ${X11_LIBRARIES})
