cmake_minimum_required(VERSION 3.0.2)
project(kuvaaja)

# Compile with C++11
set (CMAKE_CXX_STANDARD 11)

# Glew
set(GLEW_VERSION "2.1.0")

# Compile external libraries
add_subdirectory(external/)

set(CONFIG_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(include/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/build/generated/Config.hpp)

include_directories(
  build/generated/
  external/glew-${GLEW_VERSION}/include/
  external/glfw/include/
  external/glm/
  external/soil/src/
  include/
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  GLEW
  glfw
  SOIL
)

# Specify output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

aux_source_directory(src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
