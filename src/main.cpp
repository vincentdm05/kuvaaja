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
#include "Texture.hpp"

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

  Scene scene;
  scene.setBackgroundColor(glm::vec3(0.2f, 0.0f, 0.1f));

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

  // Cube
  Renderable *cubeRenderable = new Renderable();
  scene.addRenderable(cubeRenderable);

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

  static GLfloat cubeColorData[nCubeVertices * 3];
  for (int i = 0; i < nCubeVertices; i++) {
    cubeColorData[i * 3] = (cubeTriangleData[i * 3] + 1) / 2.0f;
    cubeColorData[i * 3 + 1] = (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
    cubeColorData[i * 3 + 2] = (cubeTriangleData[i * 3 + 2] + 1) / 2.0f;
  }
  cubeRenderable->setColorData(cubeColorData, nCubeVertices);

  Texture *texture = new Texture();
  texture->loadTestData();
  cubeRenderable->setTexture(texture);
  static const GLfloat cubeUvData[] = {
    1.0f, 0.0f, // -1.0f, -1.0f, -1.0f,
    0.0f, 0.0f, // -1.0f, -1.0f, 1.0f,
    0.0f, 1.0f, // -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, -1.0f,
    0.0f, 0.0f, // -1.0f, -1.0f, -1.0f,
    0.0f, 1.0f, // -1.0f, 1.0f, -1.0f,
    1.0f, 0.0f, // 1.0f, -1.0f, 1.0f,
    0.0f, 1.0f, // -1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, // 1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, -1.0f,
    1.0f, 0.0f, // 1.0f, -1.0f, -1.0f,
    0.0f, 0.0f, // -1.0f, -1.0f, -1.0f,
    1.0f, 0.0f, // -1.0f, -1.0f, -1.0f,
    0.0f, 1.0f, // -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, // -1.0f, 1.0f, -1.0f,
    1.0f, 0.0f, // 1.0f, -1.0f, 1.0f,
    0.0f, 0.0f, // -1.0f, -1.0f, 1.0f,
    0.0f, 1.0f, // -1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, // -1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, // -1.0f, -1.0f, 1.0f,
    0.0f, 0.0f, // 1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, // 1.0f, -1.0f, -1.0f,
    0.0f, 1.0f, // 1.0f, 1.0f, -1.0f,
    0.0f, 0.0f, // 1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, // 1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, // 1.0f, 1.0f, -1.0f,
    0.0f, 0.0f, // -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, // 1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, // -1.0f, 1.0f, -1.0f,
    0.0f, 1.0f, // -1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, // 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, // -1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, // 1.0f, -1.0f, 1.0f
  };
//  static GLfloat cubeUvData[nCubeVertices * 2];
//  for (int i = 0; i < nCubeVertices; i++) {
//    if (cubeTriangleData[i * 3 + 2] == -1.0f) {
//      cubeUvData[i * 2] = (cubeTriangleData[i * 3] + 1) / 2.0f;
//      cubeUvData[i * 2 + 1] = (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
//    } else {
//      cubeUvData[i * 2] = 1 - (cubeTriangleData[i * 3] + 1) / 2.0f;
//      cubeUvData[i * 2 + 1] = 1 - (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
//    }
//  }
  cubeRenderable->setUvData(cubeUvData, nCubeVertices);

//  // Single triangle
//  Renderable *triangleRenderable = new Renderable();
//  scene.addRenderable(triangleRenderable);

//  static GLfloat triangleData[] = {
//    -1.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 0.0f,
//    0.0f, 1.0f, 0.0f
//  };
//  const GLuint nTriangleVertices = sizeof(triangleData) / (3 * sizeof(GLfloat));
//  triangleRenderable->setVertexData(triangleData, nTriangleVertices);

//  static GLfloat triangleColorData[] = {
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f
//  };
//  triangleRenderable->setColorData(triangleColorData, nTriangleVertices);
//  triangleRenderable->translate(glm::vec3(-1.0f, 0.0f, 1.0f));

  // Create shaders
  std::string shaderFolder = "shaders/";
  ShaderProgram *shaderProgram = new ShaderProgram();
  shaderProgram->setShader(shaderFolder + "vertex.glsl", ST_VERTEX);
  shaderProgram->setShader(shaderFolder + "fragment.glsl", ST_FRAGMENT);
  shaderProgram->linkShaders();
  cubeRenderable->setProgram(shaderProgram);
//  triangleRenderable->setProgram(shaderProgram);
  shaderProgram->setUniform(Uniform::MVP);
  shaderProgram->setUniform(Uniform::TEXTURE);

  // Render loop
  do {
    scene.render();

    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  delete texture;
  delete shaderProgram;
  delete camera;
  scene.deleteAllRenderables();

  glfwTerminate();

  return 0;
}
