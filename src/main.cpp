#include "Camera.hpp"
#include "Context.hpp"
#include "Control.hpp"
#include "Debug.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"
#include "Renderable.hpp"
#include "Scene.hpp"
#include "ShaderDataManager.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  Context *context;
  try
  {
    context = new Context();
  }
  catch (const char *error)
  {
    std::cerr << error << std::endl;
    return -1;
  }

  Scene scene;
  scene.setBackgroundColor(0.2f, 0.0f, 0.1f);
  context->setScene(&scene);

  // Shine light
  scene.setAmbientLight(1.0f, 1.0f, 1.0f, 0.2f);
  DirectionalLight directionalLight;
  directionalLight.setColor(glm::vec3(0.2f, 0.5f, 0.1f));
  directionalLight.setDirection(glm::vec3(0.5f, -1.0f, 0.5f));
  scene.addDirectionalLight(&directionalLight);

  // Setup camera
  Camera camera;
  camera.setPosition(glm::vec3(4.0f, 3.0f, 3.0f));
  camera.setDirection(glm::vec3(-1.5f, -1.0f, -1.0f));
  camera.setUp(glm::vec3(0.0f, 1.0f, 0.0f));
  camera.setFoV(45.0f);
  camera.setAspectRatio((float) context->windowWidth() / context->windowHeight());
  camera.setNear(0.1f);
  camera.setFar(100.0f);
  scene.setCamera(&camera);

  // Create shaders
  std::string shaderFolder = "shaders/";
  ShaderProgram shaderProgram;
  shaderProgram.setShader(shaderFolder + "vertex.glsl", ShaderType::VERTEX);
  shaderProgram.setShader(shaderFolder + "fragment.glsl", ShaderType::FRAGMENT);

  // Create materials
  Material cubeMaterial;
  cubeMaterial.setProgram(&shaderProgram);
  Material triangleMaterial;
  triangleMaterial.setProgram(&shaderProgram);

  // Cube
  Renderable cubeRenderable;
  cubeRenderable.setMaterial(&cubeMaterial);
  scene.addRenderable(&cubeRenderable);

  const float cubeTriangleData[] =
  {
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
  cubeRenderable.setVertexData(cubeTriangleData, nCubeVertices);
  cubeRenderable.scale(0.75f, 0.75f, 0.75f);

  // TODO: compute actual normal
  std::vector<glm::vec3> cubeNormals;
  for (int i = 0; i < nCubeVertices; i++)
  {
    glm::vec3 normal = -glm::normalize(glm::vec3(cubeTriangleData[3 * i], cubeTriangleData[3 * i + 1], cubeTriangleData[3 * i + 2]));
    cubeNormals.push_back(normal);
  }
  cubeRenderable.setNormalData(cubeNormals);

  static float cubeColorData[nCubeVertices * 3];
  for (int i = 0; i < nCubeVertices; i++)
  {
    cubeColorData[i * 3] = (cubeTriangleData[i * 3] + 1) / 2.0f;
    cubeColorData[i * 3 + 1] = (cubeTriangleData[i * 3 + 1] + 1) / 2.0f;
    cubeColorData[i * 3 + 2] = (cubeTriangleData[i * 3 + 2] + 1) / 2.0f;
  }
  cubeRenderable.setColorData(cubeColorData, nCubeVertices);

  Texture texture;
//  texture.loadTestData();
  texture.load("resources/images/img_test.png");
  cubeRenderable.material()->setTexture(&texture);
  const float cubeUvData[] =
  {
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
  cubeRenderable.setUvData(cubeUvData, nCubeVertices);

  // Single triangle
  Renderable triangleRenderable;
  triangleRenderable.setMaterial(&triangleMaterial);
  scene.addRenderable(&triangleRenderable);

  const float triangleData[] =
  {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  const unsigned int nTriangleVertices = sizeof(triangleData) / (3 * sizeof(float));
  triangleRenderable.setVertexData(triangleData, nTriangleVertices);
  triangleRenderable.rotate(1.2f, 0.0f, 1.0f, 0.0);
  triangleRenderable.scale(3.0f, 3.0f, 1.0f);

  std::vector<glm::vec3> triangleNormalData;
  for (int i = 0; i < nTriangleVertices; i++)
    triangleNormalData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
  triangleRenderable.setNormalData(triangleNormalData);

  const float triangleColorData[] =
  {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  triangleRenderable.setColorData(triangleColorData, nTriangleVertices);

  const float triangleUvData[] =
  {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
  };
  triangleRenderable.setUvData(triangleUvData, nTriangleVertices);
  Texture triangleTexture;
  triangleTexture.loadTestData();
  triangleRenderable.material()->setTexture(&triangleTexture);

  // Generic controls
  Control control;
  control.setContext(context);
  control.setCamera(&camera);

  // Render loop
  double deltaTime;
  double stopWatch = 0.0f;
  bool showFPS = false;
  while (context->canRender())
  {
    control.gatherInput();
    control.updateCamera();

    deltaTime = context->loopTime();

    if (control.iPressed())
    {
      showFPS = !showFPS;
      if (!showFPS)
        std::cout << std::endl;
    }
    if (showFPS)
    {
      stopWatch += deltaTime;
      if (stopWatch > 0.5f)
      {
        std::cout << "\r" << std::setw(10) << deltaTime << " ms/frame (" << (int)(1 / deltaTime) << std::setw(3) << " FPS)" << std::setw(10) << std::setfill(' ') << std::flush;
        stopWatch = 0.0f;
      }
    }

    cubeRenderable.rotate(deltaTime, 1.0f, 1.0f, 0.0f);
//    triangleRenderable.rotate(deltaTime, 0.0f, 1.0f, 0.0f);

    context->render();
  }
  if (showFPS)
    std::cout << std::endl;

  delete context;

  printOpenGlErrors();

  return 0;
}
