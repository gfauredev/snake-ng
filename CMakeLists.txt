#**********************************************************************#
# Authors: Fankam Jisèle, Fauré Guilhem, Tessier Anaël                 #
#**********************************************************************#

cmake_minimum_required(VERSION 3.30)
project(SnakeNG VERSION 0.0.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") # Tous avertissements/erreurs

set(MAIN snake)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
# pkg_check_modules(SDL3_TTF REQUIRED SDL3_ttf)

add_executable(${MAIN} main.c)

include_directories(${SDL3_INCLUDE_DIRS}) # ${SDL3_TTF_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE_NAME} ${SDL3_LIBRARIES})
# ${SDL2_TTF_LIBRARIES})
