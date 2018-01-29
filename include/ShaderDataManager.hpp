#ifndef SHADER_DATA_MANAGER_HPP
#define SHADER_DATA_MANAGER_HPP

#include "Common.hpp"

#include "ShaderData.hpp"

#include <map>
#include <string>
#include <vector>

class ShaderProgram;

class ShaderDataManager {
public:
  static ShaderDataManager &shaderDataManagerReference();

  bool declareUniform(ShaderProgram *shaderProgram, UniformType uniformType);
  bool declareUniformBuffer(ShaderProgram *shaderProgram, const std::string &uniformBufferName);

  GLint getUniformLocation(ShaderProgram *shaderProgram, UniformType uniformType);

private:
  ShaderDataManager();
  ~ShaderDataManager();

  bool declareUniform(ShaderProgram *shaderProgram, UniformType uniformType, const std::string &uniformName);
  void initUbo(GLuint shaderProgramName, const std::string &uniformBufferName, GLuint &uboName, GLuint &uboBlockIndex, GLuint &uboBindingPoint);

  static GLuint cUboBindingPoints;
  bool mUboDirty;
  GLuint mUniformBufferObjectName;
  GLuint mUniformBufferObjectBlockIndex;
  GLuint mUniformBufferBindingPoint;

  struct Uniform {
    Uniform(GLint l, UniformType t, const std::string &n)
      : location(l)
      , type(t)
      , name(n)
    {}
    bool operator==(const Uniform &other) {
      // A Uniform is uniquely identified by its name
      return name == other.name;
    }
    GLint location;
    UniformType type;
    std::string name;
  };

  typedef std::map<ShaderProgram *, std::vector<Uniform> > UniformLocationContainer;
  UniformLocationContainer mUniformLocations;
};

#endif // SHADER_DATA_MANAGER_HPP
