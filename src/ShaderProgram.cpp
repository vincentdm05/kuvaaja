#include "ShaderProgram.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

ShaderProgram::ShaderProgram() :
  mProgramName(0),
  mMvpLocation(0) {}

bool ShaderProgram::load(const char* vertexShaderPath, const char* fragmentShaderPath) {
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string vertexShaderCode;
  std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
  if (vertexShaderStream.is_open()) {
    std::string line = "";
    while (getline(vertexShaderStream, line))
      vertexShaderCode += "\n" + line;
    vertexShaderStream.close();
  } else {
    printf("Impossible to open vertex shader at \"%s\".\n", vertexShaderPath);
    return false;
  }

  // Read the Fragment Shader code from the file
  std::string fragmentShaderCode;
  std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);
  if (fragmentShaderStream.is_open()) {
    std::string line = "";
    while (getline(fragmentShaderStream, line))
      fragmentShaderCode += "\n" + line;
    fragmentShaderStream.close();
  } else {
    printf("Impossible to open fragment shader at \"%s\".\n", fragmentShaderPath);
    return false;
  }

  GLint result = GL_FALSE;
  int infoLogLength;


  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertexShaderPath);
  char const * vertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
  glCompileShader(vertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
    printf("%s\n", &vertexShaderErrorMessage[0]);
  }



  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragmentShaderPath);
  char const * fragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
  glCompileShader(fragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
    printf("%s\n", &fragmentShaderErrorMessage[0]);
  }



  // Link the program
  printf("Linking program\n");
  mProgramName = glCreateProgram();
  glAttachShader(mProgramName, vertexShaderID);
  glAttachShader(mProgramName, fragmentShaderID);
  glLinkProgram(mProgramName);

  // Check the program
  glGetProgramiv(mProgramName, GL_LINK_STATUS, &result);
  glGetProgramiv(mProgramName, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> programErrorMessage(infoLogLength + 1);
    glGetProgramInfoLog(mProgramName, infoLogLength, NULL, &programErrorMessage[0]);
    printf("%s\n", &programErrorMessage[0]);
  }

  glDetachShader(mProgramName, vertexShaderID);
  glDetachShader(mProgramName, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return true;
}

void ShaderProgram::setUniform(Uniform uniform) {
  switch (uniform) {
  case MVP:
    mMvpLocation = glGetUniformLocation(mProgramName, "mvp");
    break;
  }
}
