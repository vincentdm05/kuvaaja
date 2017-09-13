#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/Glew.h>
#include <glm/glm.hpp>

#include <vector>

class Camera;
class Renderable;

class Scene {
public:
  Scene();
  ~Scene() {}

  void setBackgroundColor(const glm::vec3 &color) { glClearColor(color.x, color.y, color.z, 1.0); }
  void setCamera(Camera *camera) { mCamera = camera; }
  void addRenderable(Renderable *renderable) { mRenderables.push_back(renderable); }
  void deleteAllRenderables();

  void render() const;

private:
  Camera *mCamera;
  std::vector<Renderable *> mRenderables;

  void setupGL() const;
};

#endif // SCENE_HPP
