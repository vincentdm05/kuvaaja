#include "Texture.hpp"

#include <SOIL.h>

Texture::Texture() :
  mTextureName(0),
  mWidth(0),
  mHeight(0) {
  glGenTextures(1, &mTextureName);
}

void Texture::loadTestData() {
  const GLuint data[] = {0xFF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF,
                         0xFFFF, 0xFF00FF, 0xFFFFFFFF, 0xFFFFFFFF,
                         0xFFFFFFFF, 0xFFFFFFFF, 0xFF, 0xFF,
                         0xFFFFFFFF, 0xFFFFFFFF, 0xFF, 0xFF};
  mWidth = mHeight = 4;

  glBindTexture(GL_TEXTURE_2D, mTextureName);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(const std::string &path) {
  glBindTexture(GL_TEXTURE_2D, mTextureName);

  int channels;
  int width, height;
  GLubyte *data = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
  mWidth = width;
  mHeight = height;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  SOIL_free_image_data(data);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
}
