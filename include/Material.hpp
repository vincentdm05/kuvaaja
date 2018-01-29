#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Common.hpp"

#include "ShaderData.hpp"

#include <vector>

class ShaderProgram;
class Texture;

class Material {
public:
  Material();
  ~Material() {}

  void setProgram(ShaderProgram *shaderProgram) { mShaderProgram = shaderProgram; }
  void setTexture(Texture *texture) {
    mTexture = texture;
    mUniformDeclarationBuffer.push_back(UniformType::TEXTURE);
  }

  void useProgram() const;

  ShaderProgram *shaderProgram() const { return mShaderProgram; }
  Texture *texture() const { return mTexture; }

private:
  ShaderProgram *mShaderProgram;
  Texture *mTexture;

  mutable std::vector<UniformType> mUniformDeclarationBuffer;

  bool unbufferUniformDeclarations() const;
};

#endif // MATERIAL_HPP
