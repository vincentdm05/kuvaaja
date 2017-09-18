#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

#include <string>

class Texture {
public:
  Texture();
  ~Texture() {}

  void loadTestData();
  void load(const std::string &path);

  GLuint name() const { return mTextureName; }

private:
  GLuint mTextureName;

  GLuint mWidth;
  GLuint mHeight;
};

#endif // TEXTURE_HPP
