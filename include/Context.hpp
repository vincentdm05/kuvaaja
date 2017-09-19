#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Scene;

class Context {
public:
  Context();
  ~Context();

  void render();
  bool canRender() const;

  double getTime() const { return glfwGetTime(); }

  GLuint windowWidth() const { return mWindowWidth; }
  GLuint windowHeight() const { return mWindowHeight; }

  void setScene(Scene *scene) { mScene = scene; }

private:
  GLFWwindow *mWindow;
  GLuint mWindowWidth;
  GLuint mWindowHeight;

  Scene *mScene;
};

#endif // CONTEXT_HPP
