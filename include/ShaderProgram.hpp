#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>

enum Uniform {
  MVP
};

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram() {}

  bool load(const char *vertexShaderPath, const char *fragmentShaderPath);
  void setUniform(Uniform uniform);

  GLuint name() { return mProgramName; }
  GLuint mvpLocation() { return mMvpLocation; }

private:
  GLuint mProgramName;
  // TODO: generalize uniform location mecanism
  GLuint mMvpLocation;
};

#endif // SHADER_PROGRAM_HPP
