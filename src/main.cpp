#include "Camera.hpp"
#include "Context.hpp"
#include "Debug.hpp"
#include "Renderable.hpp"
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  Context *context;
  try {
    context = new Context();
  } catch (const char *error) {
    std::cerr << error << std::endl;
    return -1;
  }

  Scene *scene = new Scene();
  scene->setBackgroundColor(0.2f, 0.0f, 0.1f);
  context->setScene(scene);

  // Setup camera
  Camera *camera = new Camera();
  camera->setPosition(4.0f, 3.0f, 3.0f);
  camera->setLookingAt(0.0f, 0.0f, 0.0f);
  camera->setUp(0.0f, 1.0f, 0.0f);
  camera->setFoV(45.0f);
  camera->setAspectRatio((float) context->windowWidth() / context->windowHeight());
  camera->setNear(0.1f);
  camera->setFar(100.0f);
  scene->setCamera(camera);

  // Cube
  Renderable *cubeRenderable = new Renderable();
  scene->addRenderable(cubeRenderable);

  const float cubeTriangleData[] = {
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
  const unsigned int nCubeVertices = sizeof(cubeTriangleData) / (3 * sizeof(float));
  cubeRenderable->setVertexData(cubeTriangleData, nCubeVertices);
  cubeRenderable->scale(0.75f, 0.75f, 0.75f);

  static float cubeColorData[nCubeVertices * 3];
  for (int i = 0; i < nCubeVertices; i++) {
    cubeColorData[i * 3] = (cubeTriangleData[i * 3] + 1) / 2.0f;
    cubeColorData[i * 3 + 1] = (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
    cubeColorData[i * 3 + 2] = (cubeTriangleData[i * 3 + 2] + 1) / 2.0f;
  }
  cubeRenderable->setColorData(cubeColorData, nCubeVertices);

  Texture *texture = new Texture();
//  texture->loadTestData();
  texture->load("resources/images/img_test.png");
  cubeRenderable->setTexture(texture);
  const float cubeUvData[] = {
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
  cubeRenderable->setUvData(cubeUvData, nCubeVertices);

  // Single triangle
  Renderable *triangleRenderable = new Renderable();
  scene->addRenderable(triangleRenderable);

  const float triangleData[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  const unsigned int nTriangleVertices = sizeof(triangleData) / (3 * sizeof(float));
  triangleRenderable->setVertexData(triangleData, nTriangleVertices);
  triangleRenderable->rotate(1.2f, 0.0f, 1.0f, 0.0);
  triangleRenderable->scale(3.0f, 3.0f, 1.0f);

  const float triangleColorData[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  triangleRenderable->setColorData(triangleColorData, nTriangleVertices);

  const float triangleUvData[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
  };
  triangleRenderable->setUvData(triangleUvData, nTriangleVertices);
  Texture *triangleTexture = new Texture();
  triangleTexture->loadTestData();
  triangleRenderable->setTexture(triangleTexture);

  // Create shaders
  std::string shaderFolder = "shaders/";
  ShaderProgram *shaderProgram = new ShaderProgram();
  shaderProgram->setShader(shaderFolder + "vertex.glsl", ShaderType::VERTEX);
  shaderProgram->setShader(shaderFolder + "fragment.glsl", ShaderType::FRAGMENT);
  shaderProgram->linkShaders();
  shaderProgram->setUniform(Uniform::MVP);
  shaderProgram->setUniform(Uniform::TEXTURE);

  cubeRenderable->setProgram(shaderProgram);
  triangleRenderable->setProgram(shaderProgram);

  // Render loop
  double time = context->getTime();
  double lastTime = time;
  double deltaTime;
  do {
    time = context->getTime();
    deltaTime = (time - lastTime);
    cubeRenderable->rotate(deltaTime, 1.0f, 1.0f, 0.0f);
    triangleRenderable->rotate(deltaTime, 0.0f, 1.0f, 0.0f);
    lastTime = time;

    context->render();

  } while (context->canRender());

  delete texture;
  delete shaderProgram;
  delete triangleTexture;
  delete camera;
  scene->deleteAllRenderables();
  delete scene;
  delete context;

  printOpenGlErrors();

  return 0;
}
