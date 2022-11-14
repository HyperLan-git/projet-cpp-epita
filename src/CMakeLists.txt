cmake_minimum_required(VERSION 3.0)

project(CPPSDL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories($(PROJECT_SOURCE_DIR)/../include/)

add_executable(main main.cpp)

add_library(sources SHARED game/Game.cpp render/Renderer.cpp render/Window.cpp)

target_link_libraries(main sources ${SDL2_LIBRARIES})
#configure_file(${CMAKE_CURRENT_BINARY_DIR}/main ${CMAKE_CURRENT_BINARY_DIR}/../main COPYONLY)