#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/glew.h>

class ShaderProgram;
class Texture;

class Material {
public:
  Material();
  ~Material() {}

  void setProgram(ShaderProgram *shaderProgram) { mShaderProgram = shaderProgram; }
  void setTexture(Texture *texture) { mTexture = texture; }

  void useProgram() const;

  ShaderProgram *shaderProgram() const { return mShaderProgram; }
  Texture *texture() const { return mTexture; }

private:
  ShaderProgram *mShaderProgram;
  Texture *mTexture;
};

#endif // MATERIAL_HPP
