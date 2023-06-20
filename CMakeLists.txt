cmake_minimum_required(VERSION 3.22.1)
project(oceanTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++20 -O3 -fsanitize=address -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/compute
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering)

add_library("${PROJECT_NAME}_lib" STATIC)
target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/include/compute
                                                        ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_lib")