#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialise GLFW.\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a context
  GLFWwindow* window;
  const GLuint windowWidth = 1024;
  const GLuint windowHeight = 768;
  window = glfwCreateWindow(windowWidth, windowHeight, "kuvaaja", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW.\n");
    glfwTerminate();
    return -1;
  }

  // Activate keyboard input
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set background color
  glClearColor(0.2f, 0.0f, 0.1f, 0.0f);

  // Create VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Test data
  const GLuint nVertices = 3;
  static const GLfloat triangle_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
  };

  // Create VBO
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);

  // Load, compile and bind shaders
  std::string shaderFolder = "shaders/";
  GLuint programID = shader::load((shaderFolder + "vertex.glsl").c_str(), (shaderFolder + "fragment.glsl").c_str());

  // Model matrix for transformation from object space to world space
  glm::mat4 model = glm::mat4(1.0f);

  // View matrix for transformation from world space to camera (or eye) space
  glm::vec3 camera = glm::vec3(4.0f, 3.0f, 3.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 view = glm::lookAt(camera, glm::vec3(0.0f), up);

  // Projection matrix for transformation from camera space to projective space
  GLfloat fieldOfView = glm::radians(45.0f);
  GLfloat aspectRatio = windowWidth / windowHeight;
  GLfloat cameraNear = 0.1f;
  GLfloat cameraFar = 100.0f;
  glm::mat4 projection = glm::perspective(fieldOfView, aspectRatio, cameraNear, cameraFar);

  glm::mat4 mvp = projection * view * model;
  GLuint mvpId = glGetUniformLocation(programID, "mvp");

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);
    glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);

    // Draw data
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, nVertices, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  glfwTerminate();

  return 0;
}
