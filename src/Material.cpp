#include "Material.hpp"

#include "ShaderDataManager.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <assert.h>
#include <iostream>

Material::Material()
  : mShaderProgram(NULL)
  , mTexture(NULL)
  , mUniformDeclarationBuffer()
{}

void Material::useProgram() const
{
  assert(mShaderProgram);
  if (!mShaderProgram) {
    std::cerr << "Material::useProgram: Missing shader program." << std::endl;
    return;
  }

  if (!unbufferUniformDeclarations()) {
    std::cerr << "Material::useProgramm: unable to declare uniforms." << std::endl;
  }

  glUseProgram(mShaderProgram->name());
}

bool Material::unbufferUniformDeclarations() const
{
  if (mUniformDeclarationBuffer.empty())
    return true;

  if (!mShaderProgram)
    return false;

  for (UniformType &u : mUniformDeclarationBuffer)
  {
    if (!ShaderDataManager::shaderDataManagerReference().declareUniform(mShaderProgram, u))
      return false;
  }
  mUniformDeclarationBuffer.clear();

  return true;
}
