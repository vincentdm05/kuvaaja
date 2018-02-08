#include "Material.hpp"

#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <assert.h>

Material::Material()
  : mShaderProgram(NULL)
  , mTexture(NULL)
{}

void Material::useProgram() const
{
  assert(mShaderProgram);
  glUseProgram(mShaderProgram->name());
}
