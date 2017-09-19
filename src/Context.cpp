#include "Context.hpp"

#include "Scene.hpp"

Context::Context() :
  mWindow(NULL),
  mWindowWidth(1024),
  mWindowHeight(768),
  mScene(NULL) {
  if (!glfwInit())
    throw "Failed to initialise GLFW.";

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "kuvaaja", NULL, NULL);
  if (mWindow == NULL) {
    glfwTerminate();
    throw "Failed to open GLFW window.";
  }
  glfwMakeContextCurrent(mWindow);
  glewExperimental = true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    throw "Failed to initialize GLEW.";
  }

  // Activate keyboard input
  glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
}

Context::~Context() {
  glfwTerminate();
}

void Context::render() {
  if (!mScene)
    return;

  mScene->render();

  glfwSwapBuffers(mWindow);
  glfwPollEvents();
}

bool Context::canRender() const {
  return glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(mWindow) == 0;
}
