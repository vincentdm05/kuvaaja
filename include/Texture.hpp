#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Common.hpp"

#include <string>

class Texture
{
public:
  Texture();
  ~Texture() {}

  enum Type
  {
    NONE,
    ALBEDO,
    NORMAL = ALBEDO << 1,
    METALNESS = NORMAL << 1,
    ROUGHNESS = METALNESS << 1
  };

  void loadTestData();
  void load(const std::string &path, Type type);

  Type type() const { return mType; }

  GLuint name() const { return mTextureName; }

private:
  GLuint mTextureName;

  Type mType;

  GLuint mWidth;
  GLuint mHeight;
};

#endif // TEXTURE_HPP
