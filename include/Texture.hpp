#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

#include <string>

class Texture {
public:
  Texture();
  ~Texture() {}

  void loadTestData();

  GLuint name() const { return mTextureName; }
  GLint unit() const { return mTextureUnit; }

private:
  GLuint mTextureName;
  static GLuint cTextureUnits;
  GLuint mTextureUnit;

  GLuint mWidth;
  GLuint mHeight;
};

#endif // TEXTURE_HPP
