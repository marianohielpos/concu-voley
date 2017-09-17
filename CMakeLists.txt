cmake_minimum_required(VERSION 3.7)
project(Concu_voley)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE Concu_voley_SOURCES "src/*.cpp")
file(GLOB_RECURSE Concu_voley_HEADERS "src/*.h")

set (Concu_voley_INCLUDE_DIRS "")
foreach (_headerFile ${Concu_voley_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Concu_voley_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Concu_voley_INCLUDE_DIRS)

include_directories(${Concu_voley_INCLUDE_DIRS})

# MESSAGE( STATUS ${Concu_voley_SOURCES})

add_executable(Concu_voley ${Concu_voley_SOURCES})
