cmake_minimum_required(VERSION 3.9)
project(KomischesPlottingDings)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

include_directories(${X11_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp Output/BmpWriter.cpp  Output/SfmlWriter.cpp Render3d.cpp Point3d.cpp Plot.cpp Pcd.cpp)
target_link_libraries(KomischesPlottingDings sfml-graphics sfml-window sfml-system)
