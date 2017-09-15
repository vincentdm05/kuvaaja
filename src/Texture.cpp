#include "Texture.hpp"

//#include <SOIL.h>

#include <stdio.h>
#include <stdlib.h>


GLuint Texture::cTextureUnits = 0;

Texture::Texture() :
  mTextureName(0),
  mWidth(0),
  mHeight(0) {
  mTextureUnit = cTextureUnits++;
}

void Texture::loadTestData() {
  const GLuint data[] = {0xFF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF,
                         0xFFFF, 0xFF00FF, 0xFFFFFFFF, 0xFFFFFFFF,
                         0xFFFFFFFF, 0xFFFFFFFF, 0xFF, 0xFF,
                         0xFFFFFFFF, 0xFFFFFFFF, 0xFF, 0xFF};
  mWidth = mHeight = 4;

  glGenTextures(1, &mTextureName);
  glBindTexture(GL_TEXTURE_2D, mTextureName);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

  glBindTexture(GL_TEXTURE_2D, 0);
}
