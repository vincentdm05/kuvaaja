#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>

#include <string>

enum ShaderType {
  ST_VERTEX = GL_VERTEX_SHADER,
  ST_FRAGMENT = GL_FRAGMENT_SHADER
};

enum Uniform {
  MVP
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

private:
  GLuint mProgramName;
  GLuint mVertexShaderName;
  GLuint mFragmentShaderName;
  // TODO: generalize uniform location mecanism
  GLuint mMvpLocation;

  void releaseShader(GLuint &shaderName);
};

#endif // SHADER_PROGRAM_HPP
