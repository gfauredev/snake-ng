#**********************************************************************#
# Authors: Fankam Jisèle, Fauré Guilhem, Tessier Anaël                 #
#**********************************************************************#
cmake_minimum_required(VERSION 3.30)
project(SnakeNG VERSION 0.0.0)
set(MAIN snake)

# Use Clang, set C standard, create main executable
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") # All the warnings and errors
add_executable(${MAIN} main.c fruit.c snake.c render.c)
set_target_properties(${MAIN} PROPERTIES C_STANDARD 23)

# Find and link libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
message(STATUS "SDL3 include dir: ${SDL3_INCLUDE_DIRS}")
message(STATUS "SDL3 libraries: ${SDL3_LIBRARIES}")
include_directories(${SDL3_INCLUDE_DIRS}) # ${SDL3_TTF_INCLUDE_DIRS})
target_link_libraries(${MAIN} PRIVATE ${SDL3_LIBRARIES}) # SDL3::SDL3)
