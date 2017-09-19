#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>

#include <string>

enum ShaderType {
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER
};

enum Uniform {
  MVP,
  TEXTURE
};

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  bool setShader(const std::string &shaderPath, ShaderType shaderType);
  bool linkShaders();
  void setUniform(Uniform uniform);

  GLuint name() const { return mProgramName; }
  GLuint mvpLocation() const { return mMvpLocation; }
  GLuint textureLocation() const { return mTextureLocation; }
  GLuint textureUnit() const { return mTextureUnit; }

private:
  GLuint mProgramName;
  GLuint mVertexShaderName;
  GLuint mFragmentShaderName;
  // TODO: generalize uniform location mecanism
  GLuint mMvpLocation;
  GLuint mTextureLocation;

  static GLuint cTextureUnits;
  GLuint mTextureUnit;

  void releaseShader(GLuint &shaderName);
};

#endif // SHADER_PROGRAM_HPP
