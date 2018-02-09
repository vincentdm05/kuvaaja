#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Common.hpp"

#include <string>

class Texture
{
public:
  Texture();
  ~Texture() {}

  void loadTestData();
  void load(const std::string &path);

  void setForcePowerOfTwo(bool value);
  void setGenerateMips(bool value);
  void setBorderRepeat(bool value);
  void setFlipVertically(bool value);

  bool getForcePowerOfTwo();
  bool getGenerateMips();
  bool getBorderRepeat();
  bool getFlipVertically();

  GLuint name() const { return mTextureName; }

private:
  GLuint mTextureName;

  GLuint mWidth;
  GLuint mHeight;

  unsigned int mSoilFlags;

  // Helper
  void setBitFlag(unsigned int flag, bool value);
};

#endif // TEXTURE_HPP
