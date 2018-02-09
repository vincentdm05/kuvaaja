#include "ShaderDataManager.hpp"

#include "ShaderProgram.hpp"

#include <algorithm>
#include <iostream>

GLuint ShaderDataManager::cUboBindingPoints = 0;

ShaderDataManager &ShaderDataManager::shaderDataManagerReference()
{
  static ShaderDataManager manager;
  return manager;
}

bool ShaderDataManager::declareUniform(ShaderProgram *shaderProgram, UniformType uniformType)
{
  switch (uniformType)
  {
  case MAT_MODEL_VIEW_PROJECTION:
    return declareUniform(shaderProgram, uniformType, "modelViewProjection");
  case MAT_INVERSE_TRANSPOSE_MODEL:
    return declareUniform(shaderProgram, uniformType, "inverseTransposeModel");
  case AMBIENT_LIGHT:
    return declareUniform(shaderProgram, uniformType, "ambientLight");
  case POINT_LIGHTS:
    return declareUniform(shaderProgram, uniformType, "pointLights");
  case DIRECTIONAL_LIGHTS:
    return declareUniform(shaderProgram, uniformType, "directionalLights");
  case SPOT_LIGHTS:
    return declareUniform(shaderProgram, uniformType, "spotLights");
  case TEXTURE:
    return declareUniform(shaderProgram, uniformType, "textureSampler");
  default:
    std::cerr << "Trying to set an unknown uniform." << std::endl;
    return false;
  }
}

bool ShaderDataManager::declareUniformBuffer(ShaderProgram *shaderProgram, const std::string &uniformBufferName)
{
  // TODO: generalise for any number of ubos
  initUbo(shaderProgram->name(), uniformBufferName, mUniformBufferObjectName, mUniformBufferObjectBlockIndex, mUniformBufferBindingPoint);
  return glIsBuffer(mUniformBufferObjectName) == GL_TRUE && mUniformBufferObjectBlockIndex != GL_INVALID_INDEX;
}

GLint ShaderDataManager::getUniformLocation(ShaderProgram *shaderProgram, UniformType uType)
{
  std::vector<Uniform> &programLocations = mUniformLocations[shaderProgram];
  if (programLocations.empty())
    return -1;

  auto compFunc = [&uType](const Uniform &uniform)
  {
    return uniform.type == uType;
  };

  std::vector<Uniform>::iterator it = std::find_if(programLocations.begin(), programLocations.end(), compFunc);
  if (it == programLocations.end())
    return -1;

  return it->location;
}

ShaderDataManager::ShaderDataManager()
  : mUboDirty(true)
  , mUniformBufferObjectName(0)
  , mUniformBufferObjectBlockIndex(0)
  , mUniformBufferBindingPoint(0)
  , mUniformLocations()
{}

ShaderDataManager::~ShaderDataManager()
{
  mUniformLocations.clear();
}

bool ShaderDataManager::declareUniform(ShaderProgram *shaderProgram, UniformType uniformType, const std::string &uniformName)
{
  assert(shaderProgram);
  if (!shaderProgram)
    return false;

  // TODO: sort out solution for uniquely identifying Uniform based on type or name (also avoid getting location each time)
  GLint location = glGetUniformLocation(shaderProgram->name(), uniformName.c_str());
  std::vector<Uniform> &programLocations = mUniformLocations[shaderProgram];
  Uniform newElement = Uniform(location, uniformType, uniformName);
  if (std::find(programLocations.begin(), programLocations.end(), newElement) == programLocations.end())
    programLocations.push_back(newElement);

  return location >= 0;
}

void ShaderDataManager::initUbo(GLuint shaderProgramName, const std::string &uniformBufferName, GLuint &uboName, GLuint &uboBlockIndex, GLuint &uboBindingPoint)
{
  glGenBuffers(1, &uboName);
  glBindBuffer(GL_UNIFORM_BUFFER, uboName);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderLights), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  uboBindingPoint = cUboBindingPoints++; // TODO: test for max
  glBindBufferBase(GL_UNIFORM_BUFFER, uboBindingPoint, uboName);

  uboBlockIndex = glGetUniformBlockIndex(shaderProgramName, uniformBufferName.c_str());
  glUniformBlockBinding(shaderProgramName, uboBlockIndex, uboBindingPoint);
}
