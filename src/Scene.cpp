#include "Scene.hpp"

#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "Renderable.hpp"
#include "ShaderProgram.hpp"
#include "SpotLight.hpp"
#include "Texture.hpp"

Scene::Scene()
  : mCamera(NULL)
  , mAmbientLight(1.0f, 1.0f, 1.0f, 1.0f)
{
  setupGL();
}

void Scene::setAmbientLight(float r, float g, float b, float intensity)
{
  mAmbientLight[0] = r;
  mAmbientLight[1] = g;
  mAmbientLight[2] = b;
  mAmbientLight[3] = intensity;
}

void Scene::deleteAllRenderables()
{
  deleteAll(mRenderables);
}

void Scene::deleteAllLights()
{
  deleteAll(mPointLights);
  deleteAll(mDirectionalLights);
  deleteAll(mSpotLights);
}

// This is a naive rendering method, it should be improved in the future.
void Scene::render() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 viewProjectionMatrix = mCamera->projectionMatrix() * mCamera->viewMatrix();

  for (Renderable *r : mRenderables)
  {
    r->material()->useProgram();

    ShaderProgram *program = r->material()->shaderProgram();
    if (!program)
      continue;

    // Update mvp for the shader
    glm::mat4 mvp = viewProjectionMatrix * r->modelMatrix();
    GLuint mvpLocation = program->matModelViewProjectionLocation();
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

    // Update inverse transpose model matrix for normals
    glm::mat4 itm = glm::transpose(glm::inverse(r->modelMatrix()));
    GLuint itmLocation = program->matInverseTransposeModelLocation();
    glUniformMatrix4fv(itmLocation, 1, GL_FALSE, &itm[0][0]);

    // Lights
    GLuint lightLocation = program->ambientLightLocation();
    mAmbientLight.useAtLocation(lightLocation);

    lightLocation = program->pointLightsLocation();
    for (PointLight *light : mPointLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    lightLocation = program->directionalLightsLocation();
    for (DirectionalLight *light : mDirectionalLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    lightLocation = program->spotLightsLocation();
    for (SpotLight *light : mSpotLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    Texture *texture = r->material()->texture();
    if (texture)
    {
      GLuint textureUnit = program->textureUnit();
      GLuint textureLocation = program->textureLocation();
      glActiveTexture(textureUnit);
      glBindTexture(GL_TEXTURE_2D, texture->name());
      glUniform1i(textureLocation, textureUnit);
    }

    r->render();
  }
}

void Scene::setupGL() const
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
}
