#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <Positionable.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram;
class Texture;

class Renderable : public Positionable {
public:
  Renderable();
  ~Renderable();

  void setVertexData(const GLfloat *data, unsigned int vertexCount) { setVaoData(data, mVertexBufferName, vertexCount, 3); mVertexCount = vertexCount; }
  void setColorData(const GLfloat *data, unsigned int pointCount) { setVaoData(data, mColorBufferName, pointCount, 3); }
  void setUvData(const GLfloat *data, unsigned int uvCount) { setVaoData(data, mUvBufferName, uvCount, 2); }
  void setProgram(ShaderProgram *shaderProgram) { mShaderProgram = shaderProgram; }
  void setTexture(Texture *texture) { mTexture = texture; }

  void useProgram() const;
  void render() const;

  glm::mat4 modelMatrix() { return transform(); }
  ShaderProgram *shaderProgram() const { return mShaderProgram; }
  Texture *texture() const { return mTexture; }

private:
  // VAO
  GLuint mVertexArrayName;
  // VBOs
  GLuint mVertexBufferName;
  GLuint mColorBufferName;
  GLuint mUvBufferName;

  ShaderProgram *mShaderProgram;
  Texture *mTexture;

  unsigned int mVertexCount;

  void setVaoData(const GLfloat *data, GLuint &bufferName, unsigned int count, unsigned int cardinality);
};

#endif // RENDERABLE_HPP
