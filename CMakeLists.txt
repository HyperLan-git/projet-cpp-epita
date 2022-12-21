cmake_minimum_required(VERSION 3.0)

project(CPPSDL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_compile_options(-fsanitize=address -g)
add_link_options(-fsanitize=address -g)

add_executable(main src/main.cpp)

add_library(sources SHARED src/game/Game.cpp src/game/World.cpp
    src/render/Renderer.cpp src/render/Window.cpp
    src/entity/Entity.cpp src/entity/Animal.cpp
    src/entity/Sheep.cpp src/entity/Wolf.cpp
    src/audio/AudioHandler.cpp)

target_link_libraries(main sources ${SDL2_LIBRARIES})