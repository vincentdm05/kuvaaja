#include "Camera.hpp"
#include "Config.hpp"
#include "Context.hpp"
#include "Control.hpp"
#include "Debug.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"
#include "model/Box.hpp"
#include "model/Triangle.hpp"
#include "model/Quad.hpp"
#include "Renderable.hpp"
#include "Scene.hpp"
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
  std::string shaderFolder = getProjectRoot() + "/shaders/";
  ShaderProgram shaderProgram;
  shaderProgram.setShader(shaderFolder + "vertex.glsl", ShaderType::VERTEX);
  shaderProgram.setShader(shaderFolder + "fragment.glsl", ShaderType::FRAGMENT);
  shaderProgram.linkShaders();
  // TODO: get rid of the need to do this from outside.
  // Instead, keep track of what is used in the program from, e.g., the scene
  shaderProgram.setUniform(Uniform::MAT_MODEL_VIEW_PROJECTION);  // For vertices
  shaderProgram.setUniform(Uniform::MAT_INVERSE_TRANSPOSE_MODEL);  // For normals
  shaderProgram.setUniform(Uniform::TEXTURE);
  shaderProgram.setUniform(Uniform::AMBIENT_LIGHT);
  shaderProgram.setUniform(Uniform::DIRECTIONAL_LIGHTS);

  // Create materials
  Material cubeMaterial;
  cubeMaterial.setProgram(&shaderProgram);
  Material texturedMaterial;
  texturedMaterial.setProgram(&shaderProgram);
  Texture texture;
//  texture.loadTestData();
  texture.load(getProjectRoot() + "/resources/images/img_test.png");
  texturedMaterial.setTexture(&texture);
  Material triangleMaterial;
  triangleMaterial.setProgram(&shaderProgram);

  // Create models
  model::Box boxModel;
  model::Triangle triangleModel;
  model::Quad quadModel;

  Renderable cube;
  cube.setMaterial(&cubeMaterial);
  cube.setModel(&boxModel);
  cube.translate(0, 3, 2);
  scene.addRenderable(&cube);

  Renderable anotherCube;
  anotherCube.setMaterial(&texturedMaterial);
  anotherCube.setModel(&boxModel);
  anotherCube.translate(0, 0, -2);
  scene.addRenderable(&anotherCube);

  const size_t nMoreCubes = 1000;
  Renderable moreCubes[nMoreCubes];
  for (size_t i = 0; i < nMoreCubes; i++)
  {
    moreCubes[i].setMaterial(&cubeMaterial);
    moreCubes[i].setModel(&boxModel);
    moreCubes[i].translate(20 * sin(i * 2 * 3.14159265359 / nMoreCubes), 2 * sin(4 * i * 2 * 3.14159265359 / nMoreCubes), 20 * cos(i * 2 * 3.14159265359 / nMoreCubes));
    moreCubes[i].rotate(i * 2 * 3.14159265359 / nMoreCubes, 0, 1, 1);
    scene.addRenderable(&moreCubes[i]);
  }

  Renderable triangle;
  triangle.setMaterial(&triangleMaterial);
  triangle.setModel(&triangleModel);
  scene.addRenderable(&triangle);

  Renderable quad;
  quad.setMaterial(&triangleMaterial);
  quad.setModel(&quadModel);
  scene.addRenderable(&quad);
  quad.translate(-3, 0, -4);

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

    cube.rotate(deltaTime, 1.0f, 1.0f, 0.0f);

    context->render();
  }
  if (showFPS)
    std::cout << std::endl;

  printOpenGlErrors("main()");

  delete context;

  return 0;
}
