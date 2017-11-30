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
  TEXTURE,
  AMBIENT_LIGHT,
  POINT_LIGHTS,
  DIRECTIONAL_LIGHTS,
  SPOT_LIGHTS
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
  GLuint ambientLightLocation() const { return mAmbientLightLocation; }
  GLuint pointLightsLocation() const { return mPointLightsLocation; }
  GLuint directionalLightsLocation() const { return mDirectionalLightsLocation; }
  GLuint spotLightsLocation() const { return mSpotLightsLocation; }
  GLuint textureLocation() const { return mTextureLocation; }
  GLuint textureUnit() const { return mTextureUnit; }

private:
  GLuint mProgramName;
  GLuint mVertexShaderName;
  GLuint mFragmentShaderName;
  // TODO: generalize uniform location mecanism
  GLuint mMvpLocation;
  GLuint mAmbientLightLocation;
  GLuint mPointLightsLocation;
  GLuint mDirectionalLightsLocation;
  GLuint mSpotLightsLocation;
  GLuint mTextureLocation;

  static GLuint cTextureUnits;
  GLuint mTextureUnit;

  void releaseShader(GLuint &shaderName);
};

#endif // SHADER_PROGRAM_HPP
