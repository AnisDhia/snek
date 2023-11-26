cmake_minimum_required(VERSION 3.26)
project(snek)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/Dev/sdl/SDL2-2.28.5/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/Dev/sdl/SDL2_ttf-2.20.2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SDL2_INCLUDE_DIR "C:/Dev/sdl/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Game.cpp
        src/Snake.cpp
        src/Snake.h
        src/Snake.h
        src/Map.cpp
        src/Map.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

