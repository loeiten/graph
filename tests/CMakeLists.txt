# Freely after
# https://github.com/albertchan/cmake-boost-demo/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Add the test binary to the same directory as the main binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Dependencies
find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

# Gather the source files for the tests
file(GLOB UNIT_TESTS_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/test_*.cxx)

# Include paths
set(UNIT_TESTS_INCLUDES ${PROJECT_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR})

# Assign the include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${UNIT_TESTS_INCLUDES})

# Build unit tests
# add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(unit_tests ${UNIT_TESTS_SRC_FILES} ${SRC_FILES})
target_link_libraries(unit_tests ${Boost_LIBRARIES})

enable_testing()
add_test(GraphTest unit_tests)
