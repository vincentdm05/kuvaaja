#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "Common.hpp"

#include <string>

enum ShaderType
{
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER
};

enum Uniform
{
  MAT_MODEL_VIEW_PROJECTION,
  MAT_INVERSE_TRANSPOSE_MODEL,
  TEXTURE,
  AMBIENT_LIGHT,
  POINT_LIGHTS,
  DIRECTIONAL_LIGHTS,
  SPOT_LIGHTS,
  UNIFORM_COUNT
};

class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

  bool setShader(const std::string &shaderPath, ShaderType shaderType);
  bool linkShaders();
  void setUniform(Uniform uniform);

  GLuint name() const { return mProgramName; }
  GLuint matModelViewProjectionLocation() const { return mMatModelViewProjectionLocation; }
  GLuint matInverseTransposeModelLocation() const { return mMatInverseTransposeModelLocation; }
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
  GLuint mMatModelViewProjectionLocation;
  GLuint mMatInverseTransposeModelLocation;
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
