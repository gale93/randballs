cmake_minimum_required(VERSION 3.0)
project(RANDBALLS)

###################################################################
# General Setting

# configure general include
include_directories(src/)

# configure compiler command
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -coverage")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")

###################################################################
# Build SFML 2.4.2 submodule
# URL: https://github.com/SFML/SFML.git

add_subdirectory(external/SFML)

###################################################################
# Build EnTT 3.3.0 submodule
# URL: https://github.com/skypjack/entt.git
set(USE_LIBCPP OFF)
add_subdirectory(external/entt)

###################################################################
#  Systems Library
file(GLOB_RECURSE SYSTEMS_SRC src/systems/*.cpp)
add_library(systems ${SYSTEMS_SRC})
target_link_libraries(systems PUBLIC sfml-system sfml-graphics sfml-window EnTT)
# target_include_directories(systems PUBLIC src/graphics/)

###################################################################
#  Graphics Library
file(GLOB_RECURSE GRAPHICS_SRC src/graphics/*.cpp)
add_library(graphics ${GRAPHICS_SRC})
target_link_libraries(graphics PUBLIC sfml-system sfml-graphics sfml-window EnTT)
target_include_directories(graphics PUBLIC src/graphics/)

###################################################################
# Engine Library
file(GLOB_RECURSE ENGINE_SRC src/engine/*.cpp)
add_library(engine ${ENGINE_SRC})
target_link_libraries(engine PUBLIC sfml-system sfml-graphics sfml-window EnTT)

###################################################################
# Engine Library
add_executable(randballs src/main.cpp)
target_link_libraries(randballs PUBLIC engine graphics systems)