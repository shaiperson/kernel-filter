cmake_minimum_required(VERSION 2.8)
project( KernelFilter )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_definitions(--std=c++11)
find_package( OpenCV REQUIRED )

set ( COMMON_SOURCES
    ${CMAKE_BINARY_DIR}/../src/KernelFilter.cpp )
set ( TEST_SOURCES
    ${CMAKE_BINARY_DIR}/../test/catch.cpp
    ${CMAKE_BINARY_DIR}/../test/test.cpp )
set ( EXAMPLE_SOURCES
    ${CMAKE_BINARY_DIR}/../example/example.cpp )


add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})
add_executable(example ${COMMON_SOURCES} ${EXAMPLE_SOURCES})

target_link_libraries( tests ${OpenCV_LIBS} )
target_link_libraries( example ${OpenCV_LIBS} )
