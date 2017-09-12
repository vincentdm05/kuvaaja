#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "Renderable.hpp"
#include "Scene.hpp"
#include "ShaderProgram.hpp"

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

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Scene scene;
  Renderable *cubeRenderable = new Renderable();
  scene.addRenderable(cubeRenderable);

  // Test data
  static GLfloat cubeTriangleData[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
  };
  const GLuint nCubeVertices = sizeof(cubeTriangleData) / (3 * sizeof(GLfloat));
  cubeRenderable->setVertexData(cubeTriangleData, nCubeVertices);

  // Generate vertex color data
  static GLfloat cubeColorData[nCubeVertices * 3];
  for (int i = 0; i < nCubeVertices; i++) {
    cubeColorData[i * 3] = (cubeTriangleData[i * 3] + 1) / 2.0f;
    cubeColorData[i * 3 + 1] = (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
    cubeColorData[i * 3 + 2] = (cubeTriangleData[i * 3 + 2] + 1) / 2.0f;
  }
  cubeRenderable->setColorData(cubeColorData, nCubeVertices);
  cubeRenderable->translate(glm::vec3(0.5f, 0.0f, -1.0f));

  // Single triangle
  Renderable *triangleRenderable = new Renderable();
  scene.addRenderable(triangleRenderable);

  static GLfloat triangleData[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  const GLuint nTriangleVertices = sizeof(triangleData) / (3 * sizeof(GLfloat));
  triangleRenderable->setVertexData(triangleData, nTriangleVertices);

  static GLfloat triangleColorData[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  triangleRenderable->setColorData(triangleColorData, nTriangleVertices);
  triangleRenderable->translate(glm::vec3(-1.0f, 0.0f, 1.0f));

  // Create shaders
  std::string shaderFolder = "shaders/";
  ShaderProgram *shaderProgram = new ShaderProgram();
  shaderProgram->load((shaderFolder + "vertex.glsl").c_str(), (shaderFolder + "fragment.glsl").c_str());
  cubeRenderable->setProgram(shaderProgram);
  triangleRenderable->setProgram(shaderProgram);
  shaderProgram->setUniform(Uniform::MVP);

  // Setup camera
  Camera *camera = new Camera();
  camera->setPosition(glm::vec3(4.0f, 3.0f, 3.0f));
  camera->setLookingAt(glm::vec3(0.0f));
  camera->setUp(glm::vec3(0.0f, 1.0f, 0.0f));
  camera->setFoV(glm::radians(45.0f));
  camera->setAspectRatio((GLfloat) windowWidth / windowHeight);
  camera->setNear(0.1f);
  camera->setFar(100.0f);
  scene.setCamera(camera);

  // Render loop
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.render();

    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  delete shaderProgram;
  delete camera;
  scene.deleteAllRenderables();

  glfwTerminate();

  return 0;
}
