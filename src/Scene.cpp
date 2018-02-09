#include "Scene.hpp"

#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "Renderable.hpp"
#include "ShaderDataManager.hpp"
#include "ShaderProgram.hpp"
#include "SpotLight.hpp"
#include "Texture.hpp"

Scene::Scene()
  : mCamera(NULL)
  , mAmbientLight(1.0f, 1.0f, 1.0f, 1.0f)
  , mPointLights()
  , mDirectionalLights()
  , mSpotLights()
  , mUniformDeclarationBuffer()
{
  setupGL();
}

void Scene::setAmbientLight(float r, float g, float b, float intensity)
{
  mAmbientLight[0] = r;
  mAmbientLight[1] = g;
  mAmbientLight[2] = b;
  mAmbientLight[3] = intensity;
  mUniformDeclarationBuffer.push_back(UniformType::AMBIENT_LIGHT);
}

void Scene::addDirectionalLight(DirectionalLight *directionalLight)
{
  mDirectionalLights.push_back(directionalLight);
  mUniformDeclarationBuffer.push_back(UniformType::DIRECTIONAL_LIGHTS);
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

// TODO: This is a naive rendering method, it should be improved in the future.
void Scene::render() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 viewProjectionMatrix = mCamera->projectionMatrix() * mCamera->viewMatrix();

  // Prepare uniforms
  if (!mUniformDeclarationBuffer.empty())
  {
    bool success = true;
    for (Renderable *r : mRenderables)
    {
      ShaderProgram *program = r->material()->shaderProgram();
      success &= program && unbufferUniformDeclarations(program);
    }
    if (success)
      mUniformDeclarationBuffer.clear();
  }

  ShaderDataManager &manager = ShaderDataManager::shaderDataManagerReference();
  for (Renderable *r : mRenderables)
  {
    r->material()->useProgram();

    ShaderProgram *program = r->material()->shaderProgram();
    if (!program)
      continue;

    // Update mvp for the shader
    glm::mat4 mvp = viewProjectionMatrix * r->modelMatrix();
    GLint mvpLocation = manager.getUniformLocation(program, UniformType::MAT_MODEL_VIEW_PROJECTION);
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

    // Update inverse transpose model matrix for normals
    glm::mat4 itm = glm::transpose(glm::inverse(r->modelMatrix()));
    GLint itmLocation = manager.getUniformLocation(program, UniformType::MAT_INVERSE_TRANSPOSE_MODEL);
    glUniformMatrix4fv(itmLocation, 1, GL_FALSE, &itm[0][0]);

    // Lights
    GLint lightLocation = manager.getUniformLocation(program, UniformType::AMBIENT_LIGHT);
    mAmbientLight.useAtLocation(lightLocation);

    lightLocation = manager.getUniformLocation(program, UniformType::POINT_LIGHTS);
    for (PointLight *light : mPointLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    lightLocation = manager.getUniformLocation(program, UniformType::DIRECTIONAL_LIGHTS);
    for (DirectionalLight *light : mDirectionalLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    lightLocation = manager.getUniformLocation(program, UniformType::SPOT_LIGHTS);
    for (SpotLight *light : mSpotLights)
    {
      light->useAtLocation(lightLocation);
      lightLocation += light->locationSize();
    }

    Texture *texture = r->material()->texture();
    if (texture)
    {
      GLint textureUnit = program->textureUnit();
      GLint textureLocation = manager.getUniformLocation(program, UniformType::TEXTURE);
      glActiveTexture(textureUnit);
      glBindTexture(GL_TEXTURE_2D, texture->name());
      glUniform1i(textureLocation, textureUnit);
    }

    r->render();
  }
}

bool Scene::unbufferUniformDeclarations(ShaderProgram *shaderProgram) const
{
  if (mUniformDeclarationBuffer.empty())
    return true;

  if (!shaderProgram)
    return false;

  ShaderDataManager &manager = ShaderDataManager::shaderDataManagerReference();
  for (UniformType &uniform : mUniformDeclarationBuffer)
  {
    if (!manager.declareUniform(shaderProgram, uniform))
      return false;
  }

  return true;
}

void Scene::setupGL() const
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
}
