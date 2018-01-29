#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "Common.hpp"

#include <string>

enum ShaderType {
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER
};

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  bool setShader(const std::string &shaderPath, ShaderType shaderType);

  GLuint name();
  GLuint textureUnit() const { return mTextureUnit; }

private:
  GLuint mProgramName;
  GLuint mVertexShaderName;
  GLuint mFragmentShaderName;

  static GLuint cTextureUnits;
  GLuint mTextureUnit;

  bool linkShaders();
  void releaseShader(GLuint &shaderName);
};

#endif // SHADER_PROGRAM_HPP
