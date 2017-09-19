#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/Glew.h>

#include <vector>

class Camera;
class Renderable;

class Scene {
public:
  Scene();
  ~Scene() {}

  void setBackgroundColor(float r, float g, float b) { glClearColor(r, g, b, 1.0); }
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
