cmake_minimum_required(VERSION 2.8)
project(kuvaaja)

find_package(OpenGL REQUIRED)

include_directories(include/)
aux_source_directory(src/. SRC_LIST)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

add_executable(${PROJECT_NAME} ${SRC_LIST})
