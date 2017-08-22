cmake_minimum_required(VERSION 3.0.2)
project(kuvaaja)

find_package(OpenGL REQUIRED)

# Compile external libraries
add_subdirectory(external/)

include_directories(
  external/glew-${GLEW_VERSION}/include/
  external/glfw/include/
  external/glm/
  include/
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  GLEW
  glfw
)

# Specify output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

aux_source_directory(src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
