cmake_minimum_required(VERSION 3.0.2)
project(kuvaaja)

# Compile with C++11
set(CMAKE_CXX_STANDARD 11)

# Output all warnings in debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Glew
set(GLEW_VERSION "2.1.0")

# Build external libraries
add_subdirectory(external/)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DKUVAAJA_DEBUG)
else ()
  add_definitions(-DKUVAAJA_RELEASE)
endif ()

set(CONFIG_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(include/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/build/generated/Config.hpp)

include_directories(
  build/generated/
  external/glew-${GLEW_VERSION}/include/
  external/glfw/include/
  external/glm/
  external/soil/src/
  external/tinyobjloader/
  include/
  include/model/
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  GLEW
  glfw
  SOIL
  tinyobjloader
)

# Specify output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
else ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
endif ()

#aux_source_directory(src/ SRC_LIST)
file(GLOB_RECURSE SRC_LIST src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
