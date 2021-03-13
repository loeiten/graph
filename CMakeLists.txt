cmake_minimum_required(VERSION 3.10)

project(Graph)

# Flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -Wconversion -g3 -Os")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

# Gather all source files
file(GLOB_RECURSE SRC_FILES src/*.cxx)
# Exclude the main
# https://stackoverflow.com/a/15551302/2786884
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cxx)

# Unit tests
add_subdirectory(tests)

# Target
add_executable(binary ${PROJECT_SOURCE_DIR}/src/main.cxx ${SRC_FILES})
