#include "Camera.hpp"
#include "Context.hpp"
#include "Control.hpp"
#include "Debug.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"
#include "Renderable.hpp"
#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <iostream>
#include <string>
#include <vector>

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

  // Shine light
  scene->setAmbientLight(1.0f, 1.0f, 1.0f, 0.2f);
  DirectionalLight *directionalLight = new DirectionalLight();
  directionalLight->setColor(glm::vec3(0.2f, 0.5f, 0.1f));
  directionalLight->setDirection(glm::vec3(0.5f, -1.0f, 0.5f));
  scene->addDirectionalLight(directionalLight);

  // Setup camera
  Camera *camera = new Camera();
  camera->setPosition(glm::vec3(4.0f, 3.0f, 3.0f));
  camera->setDirection(glm::vec3(-1.5f, -1.0f, -1.0f));
  camera->setUp(glm::vec3(0.0f, 1.0f, 0.0f));
  camera->setFoV(45.0f);
  camera->setAspectRatio((float) context->windowWidth() / context->windowHeight());
  camera->setNear(0.1f);
  camera->setFar(100.0f);
  scene->setCamera(camera);

  // Create shaders
  std::string shaderFolder = "shaders/";
  ShaderProgram *shaderProgram = new ShaderProgram();
  shaderProgram->setShader(shaderFolder + "vertex.glsl", ShaderType::VERTEX);
  shaderProgram->setShader(shaderFolder + "fragment.glsl", ShaderType::FRAGMENT);
  shaderProgram->linkShaders();
  // TODO: get rid of the need to do this from outside.
  // Instead, keep track of what is used in the program from, e.g., the scene
  shaderProgram->setUniform(Uniform::MAT_MODEL_VIEW_PROJECTION);  // For vertices
  shaderProgram->setUniform(Uniform::MAT_INVERSE_TRANSPOSE_MODEL);  // For normals
  shaderProgram->setUniform(Uniform::TEXTURE);
  shaderProgram->setUniform(Uniform::AMBIENT_LIGHT);
  shaderProgram->setUniform(Uniform::DIRECTIONAL_LIGHTS);

  // Create materials
  Material *cubeMaterial = new Material();
  cubeMaterial->setProgram(shaderProgram);
  Material *triangleMaterial = new Material();
  triangleMaterial->setProgram(shaderProgram);

  // Cube
  Renderable *cubeRenderable = new Renderable();
  cubeRenderable->setMaterial(cubeMaterial);
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

  // TODO: compute actual normal
  std::vector<glm::vec3> cubeNormals;
  for (int i = 0; i < nCubeVertices; i++) {
    glm::vec3 normal = -glm::normalize(glm::vec3(cubeTriangleData[3 * i], cubeTriangleData[3 * i + 1], cubeTriangleData[3 * i + 2]));
    cubeNormals.push_back(normal);
  }
  cubeRenderable->setNormalData(cubeNormals);

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
  cubeRenderable->material()->setTexture(texture);
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
  triangleRenderable->setMaterial(triangleMaterial);
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

  std::vector<glm::vec3> triangleNormalData;
  for (int i = 0; i < nTriangleVertices; i++)
    triangleNormalData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
  triangleRenderable->setNormalData(triangleNormalData);

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
  triangleRenderable->material()->setTexture(triangleTexture);

  // Generic controls
  Control *control = new Control();
  control->setContext(context);
  control->setCamera(camera);

  // Render loop
  double deltaTime;
  while (context->canRender()) {
    deltaTime = context->loopTime();
    cubeRenderable->rotate(deltaTime, 1.0f, 1.0f, 0.0f);
//    triangleRenderable->rotate(deltaTime, 0.0f, 1.0f, 0.0f);

    control->updateCamera();

    context->render();
  }

  delete control;
  delete texture;
  delete shaderProgram;
  delete cubeMaterial;
  delete triangleMaterial;
  delete triangleTexture;
  delete camera;
  scene->deleteAllRenderables();
  scene->deleteAllLights();
  delete scene;
  delete context;

  printOpenGlErrors();

  return 0;
}
