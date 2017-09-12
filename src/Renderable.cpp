#include "Renderable.hpp"

#include "ShaderProgram.hpp"

Renderable::Renderable() :
  mVertexArrayName(0),
  mVertexBufferName(0),
  mColorBufferName(0),
  mShaderProgram(NULL),
  mVertexCount(0) {
  glGenVertexArrays(1, &mVertexArrayName);
}

Renderable::~Renderable() {
  glDeleteBuffers(1, &mVertexBufferName);
  glDeleteBuffers(1, &mColorBufferName);
  glDeleteVertexArrays(1, &mVertexArrayName);
}

void Renderable::setVertexData(const GLfloat *data, unsigned int vertexCount) {
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(mVertexBufferName) == GL_TRUE)
    glDeleteBuffers(1, &mVertexBufferName);

  glGenBuffers(1, &mVertexBufferName);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferName);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), data, GL_STATIC_DRAW);

  mVertexCount = vertexCount;

  glBindVertexArray(0);
}

void Renderable::setColorData(const GLfloat *data, unsigned int pointCount) {
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(mColorBufferName) == GL_TRUE)
    glDeleteBuffers(1, &mColorBufferName);

  glGenBuffers(1, &mColorBufferName);
  glBindBuffer(GL_ARRAY_BUFFER, mColorBufferName);
  glBufferData(GL_ARRAY_BUFFER, pointCount * 3 * sizeof(GLfloat), data, GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void Renderable::useProgram() const {
  assert(mShaderProgram);
  glUseProgram(mShaderProgram->name());
}

void Renderable::render() const {
  glBindVertexArray(mVertexArrayName);

  // Draw data
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferName);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  if (mColorBufferName != 0) {
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferName);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  }

  glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
  glDisableVertexAttribArray(0);

  glBindVertexArray(0);
}
