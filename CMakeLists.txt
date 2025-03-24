#**********************************************************************#
# Authors: Fankam Jisèle, Fauré Guilhem, Tessier Anaël                 #
#**********************************************************************#

cmake_minimum_required(VERSION 3.30)
project(SnakeNG VERSION 0.0.0)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") # Afficher tous les messages d’erreur

set(MAIN snake)

add_executable(${MAIN} main.c)

# target_link_libraries(${EXECUTABLE_NAME} example) # TODO ajouter SDL3…
