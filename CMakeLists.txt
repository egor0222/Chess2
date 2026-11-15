cmake_minimum_required(VERSION 3.16)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

add_executable(chess
	src/main.cpp
	src/global.cpp
	src/draw.cpp
	src/TextureLoader.cpp
	src/logic.cpp
)

target_include_directories(chess PRIVATE include)
target_link_libraries(chess PRIVATE
	sfml-graphics
	sfml-window
	sfml-system
)
