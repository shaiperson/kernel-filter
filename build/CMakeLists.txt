cmake_minimum_required(VERSION 2.8)
project( KernelFilter )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_definitions(--std=c++11)
find_package( OpenCV REQUIRED )

set ( TEST_SOURCES
    ${CMAKE_BINARY_DIR}/../test/catch.cpp
    ${CMAKE_BINARY_DIR}/../test/convolverTests.cpp )
set ( EXAMPLE_SOURCES
    ${CMAKE_BINARY_DIR}/../example/example.cpp )


add_executable(tests ${TEST_SOURCES})
add_executable(example ${EXAMPLE_SOURCES})

target_link_libraries( tests ${OpenCV_LIBS} )
target_link_libraries( example ${OpenCV_LIBS} )
