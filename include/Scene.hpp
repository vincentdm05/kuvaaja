#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/Glew.h>
#include <glm/glm.hpp>

#include "Light.hpp"

#include <vector>

class Camera;
class DirectionalLight;
class PointLight;
class Renderable;
class SpotLight;

class Scene {
public:
  Scene();
  ~Scene() {}

  void setBackgroundColor(float r, float g, float b) { glClearColor(r, g, b, 1.0); }
  void setCamera(Camera *camera) { mCamera = camera; }
  void addRenderable(Renderable *renderable) { mRenderables.push_back(renderable); }

  void setAmbientLight(float r, float g, float b, float intensity);
  void addPointLight(PointLight *pointLight) { mPointLights.push_back(pointLight); }
  void addDirectionalLight(DirectionalLight *directionalLight) { mDirectionalLights.push_back(directionalLight); }
  void addSpotLight(SpotLight *spotLight) { mSpotLights.push_back(spotLight); }
  void deleteAllRenderables();
  void deleteAllLights();

  void render() const;

private:
  Camera *mCamera;
  std::vector<Renderable *> mRenderables;

  Light mAmbientLight;
  std::vector<PointLight *> mPointLights;
  std::vector<DirectionalLight *> mDirectionalLights;
  std::vector<SpotLight *> mSpotLights;

  void setupGL() const;

  // Helper function
  template<class T> void deleteAll(std::vector<T> &elements);
};

template<class T>
void Scene::deleteAll(std::vector<T> &elements) {
  for (T e : elements) {
    delete e;
    e = NULL;
  }
  elements.clear();
}

#endif // SCENE_HPP
