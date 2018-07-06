#### External libraries
cmake_minimum_required(VERSION 3.0.2)

### GLFW ###
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")

add_subdirectory(glfw)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
  ${OPENGL_LIBRARY}
  -lGL -lGLU -lXrandr -lXext -lX11 -lrt
  ${CMAKE_DL_LIBS}
  ${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
  ${OPENGL_LIBRARY}
  ${CMAKE_DL_LIBS}
  ${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

add_definitions(
  -DGLEW_STATIC
)

set(GLEW_SOURCE
  glew-${GLEW_VERSION}/src/glew.c
)

add_library( GLEW STATIC
  ${GLEW_SOURCE}
)

target_link_libraries(GLEW
  ${OPENGL_LIBRARY}
)

### SOIL ###

add_subdirectory(soil)

### ASSIMP ###

set(ASSIMP_NO_EXPORT true)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT false)

set(ASSIMP_BUILD_OBJ_IMPORTER true)

add_subdirectory(assimp)
