#include "Scene.hpp"

#include "Camera.hpp"
#include "Renderable.hpp"
#include "ShaderProgram.hpp"

Scene::Scene() :
  mCamera(NULL) {}

void Scene::deleteAllRenderables() {
  for (Renderable *r : mRenderables) {
    delete r;
    r = NULL;
  }
  mRenderables.clear();
}

void Scene::render() {
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
