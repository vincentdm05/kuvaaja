#include "Scene.hpp"

#include "Camera.hpp"
#include "Renderable.hpp"
#include "ShaderProgram.hpp"

Scene::Scene() :
  mCamera(NULL) {
  setupGL();
}

void Scene::deleteAllRenderables() {
  for (Renderable *r : mRenderables) {
    delete r;
    r = NULL;
  }
  mRenderables.clear();
}

void Scene::render() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 viewProjectionMatrix = mCamera->projectionMatrix() * mCamera->viewMatrix();

  for (Renderable *r : mRenderables) {
    r->useProgram();

    // Update mvp for the shader
    glm::mat4 mvp = viewProjectionMatrix * r->modelMatrix();
    GLuint mvpLocation = r->shaderProgram()->mvpLocation();
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

    r->render();
  }
}

void Scene::setupGL() const {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}
