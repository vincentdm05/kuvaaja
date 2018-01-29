#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Common.hpp"

#include <GLFW/glfw3.h>

#include <utility>

class Scene;

enum KeyType {
  KEY_A = GLFW_KEY_A,
  KEY_D = GLFW_KEY_D,
  KEY_E = GLFW_KEY_E,
  KEY_F = GLFW_KEY_F,
  KEY_Q = GLFW_KEY_Q,
  KEY_R = GLFW_KEY_R,
  KEY_S = GLFW_KEY_S,
  KEY_W = GLFW_KEY_W,
  KEY_RIGHT = GLFW_KEY_RIGHT,
  KEY_LEFT = GLFW_KEY_LEFT,
  KEY_DOWN = GLFW_KEY_DOWN,
  KEY_UP = GLFW_KEY_UP,
  KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
  KEY_LEFT_CTRL = GLFW_KEY_LEFT_CONTROL,
  KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
  KEY_RIGHT_CTRL = GLFW_KEY_RIGHT_CONTROL
};

class Context {
public:
  Context();
  ~Context();

  void render();
  bool canRender() const;

  double loopTime() const { return glfwGetTime() - mTimeBeforeLastRender; }
  void cursorPosition(double *x, double *y) const { glfwGetCursorPos(mWindow, x, y); }
  bool keyPressed(KeyType key) const { return glfwGetKey(mWindow, key) == GLFW_PRESS; }
  template <typename ...Tail>
  bool keyPressed(KeyType key, Tail&&... tail) const {
    return glfwGetKey(mWindow, key) == GLFW_PRESS || keyPressed(std::forward<Tail>(tail)...);
  }

  GLuint windowWidth() const { return mWindowWidth; }
  GLuint windowHeight() const { return mWindowHeight; }

  void setScene(Scene *scene) { mScene = scene; }

private:
  GLFWwindow *mWindow;
  GLuint mWindowWidth;
  GLuint mWindowHeight;

  Scene *mScene;

  double mTimeBeforeLastRender;
};

#endif // CONTEXT_HPP
