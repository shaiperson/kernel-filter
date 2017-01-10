cmake_minimum_required(VERSION 2.8)
project( KernelFilter )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_definitions(--std=c++11)
find_package( OpenCV REQUIRED )
add_executable (
    KernelFilter
    ${CMAKE_BINARY_DIR}/../src/KernelFilter.cpp
    ${CMAKE_BINARY_DIR}/../src/KernelSumSlider.cpp
    ${CMAKE_BINARY_DIR}/../test/test.cpp
)
target_link_libraries( KernelFilter ${OpenCV_LIBS} )
