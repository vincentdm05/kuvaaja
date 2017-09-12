#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

class Camera;
class Renderable;

class Scene {
public:
  Scene();
  ~Scene() {}

  void setCamera(Camera *camera) { mCamera = camera; }
  void addRenderable(Renderable *renderable) { mRenderables.push_back(renderable); }
  void deleteAllRenderables();

  void render();

private:
  Camera *mCamera;
  std::vector<Renderable *> mRenderables;
};

#endif // SCENE_HPP
