#include "ShaderProgram.hpp"

#include <fstream>
#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram() :
  mProgramName(0),
  mVertexShaderName(0),
  mFragmentShaderName(0),
  mMvpLocation(0),
  mTextureLocation(0) {}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(mProgramName);
}

bool ShaderProgram::setShader(const std::string &shaderPath, ShaderType shaderType) {
  GLuint &shaderName = shaderType == ST_VERTEX ? mVertexShaderName : mFragmentShaderName;
  shaderName = glCreateShader(shaderType);

  // Read shader code from file
  std::string shaderCode;
  std::ifstream fileStream(shaderPath.c_str(), std::ios::in);
  if (fileStream.is_open()) {
    std::string line = "";
    while (getline(fileStream, line))
      shaderCode += "\n" + line;
    fileStream.close();
  } else {
    std::cerr << "Impossible to open shader at \"" << shaderPath << "\".\n";
    return false;
  }

  // Compile
  const char *shaderCodeArray = shaderCode.c_str();
  glShaderSource(shaderName, 1, &shaderCodeArray, NULL);
  glCompileShader(shaderName);

  // Check
  GLint result = GL_FALSE;
  glGetShaderiv(shaderName, GL_COMPILE_STATUS, &result);
  GLint infoLogLength;
  glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> errorMessage(infoLogLength+1);
    glGetShaderInfoLog(shaderName, infoLogLength, NULL, &errorMessage[0]);
    printf("%s\n", &errorMessage[0]);
  }

  if (result != GL_TRUE) {
    releaseShader(shaderName);
    return false;
  }
  return true;
}

bool ShaderProgram::linkShaders() {
  // Link
  mProgramName = glCreateProgram();
  glAttachShader(mProgramName, mVertexShaderName);
  glAttachShader(mProgramName, mFragmentShaderName);
  glLinkProgram(mProgramName);

  // Check
  GLint result = GL_FALSE;
  glGetProgramiv(mProgramName, GL_LINK_STATUS, &result);
  GLint infoLogLength;
  glGetProgramiv(mProgramName, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> errorMessage(infoLogLength + 1);
    glGetProgramInfoLog(mProgramName, infoLogLength, NULL, &errorMessage[0]);
    printf("%s\n", &errorMessage[0]);
  }

  // Cleanup
  releaseShader(mVertexShaderName);
  releaseShader(mFragmentShaderName);

  return result == GL_TRUE;
}

void ShaderProgram::setUniform(Uniform uniform) {
  switch (uniform) {
  case MVP:
    mMvpLocation = glGetUniformLocation(mProgramName, "mvp");
    break;
  case TEXTURE:
    mTextureLocation = glGetUniformLocation(mProgramName, "textureSampler");
    break;
  }
}

void ShaderProgram::releaseShader(GLuint &shaderName) {
  glDetachShader(mProgramName, shaderName);
  glDeleteShader(shaderName);
  shaderName = 0;
}
