#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <Positionable.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram;

class Renderable : Positionable {
public:
  Renderable();
  ~Renderable();

  void setVertexData(const GLfloat *data, unsigned int vertexCount);
  void setColorData(const GLfloat *data, unsigned int pointCount);
  void setProgram(ShaderProgram *shaderProgram) { mShaderProgram = shaderProgram; }

  void useProgram() const;
  void render() const;

  void translate(glm::vec3 direction) { Positionable::translate(direction); }

  glm::mat4 modelMatrix() const { return transform(); }
  ShaderProgram *shaderProgram() const { return mShaderProgram; }

private:
  // VAO
  GLuint mVertexArrayName;
  // VBOs
  GLuint mVertexBufferName;
  GLuint mColorBufferName;

  // Shader program
  ShaderProgram *mShaderProgram;

  unsigned int mVertexCount;
};

#endif // RENDERABLE_HPP
