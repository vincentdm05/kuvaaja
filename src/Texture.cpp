#include "Texture.hpp"

#include <SOIL.h>

Texture::Texture()
  : mTextureName(0)
  , mWidth(0)
  , mHeight(0)
{
  glGenTextures(1, &mTextureName);
}

void Texture::loadTestData()
{
  const GLuint data[] =
  {
    0x000000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x0000FFFF, 0x00FF00FF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x000000FF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x000000FF, 0x000000F
  };
  mWidth = mHeight = 4;

  glBindTexture(GL_TEXTURE_2D, mTextureName);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(const std::string &path)
{
  mTextureName = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, mTextureName,
                                       SOIL_FLAG_MIPMAPS |
                                       SOIL_FLAG_TEXTURE_REPEATS |
                                       SOIL_FLAG_INVERT_Y
                                       );

  glBindTexture(GL_TEXTURE_2D, mTextureName);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
}
