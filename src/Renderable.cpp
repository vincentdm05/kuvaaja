#include "Renderable.hpp"

#include "ShaderProgram.hpp"

Renderable::Renderable() :
  mVertexArrayName(0),
  mVertexBufferName(0),
  mColorBufferName(0),
  mUvBufferName(0),
  mShaderProgram(NULL),
  mTexture(NULL),
  mVertexCount(0) {
  glGenVertexArrays(1, &mVertexArrayName);
}

Renderable::~Renderable() {
  glDeleteBuffers(1, &mVertexBufferName);
  glDeleteBuffers(1, &mColorBufferName);
  glDeleteBuffers(1, &mUvBufferName);
  glDeleteVertexArrays(1, &mVertexArrayName);
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

  if (mUvBufferName != 0) {
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, mUvBufferName);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  }

  glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
  glDisableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Renderable::setVaoData(const GLfloat *data, GLuint &bufferName, unsigned int count, unsigned int cardinality) {
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(bufferName) == GL_TRUE)
    glDeleteBuffers(1, &bufferName);

  glGenBuffers(1, &bufferName);
  glBindBuffer(GL_ARRAY_BUFFER, bufferName);
  glBufferData(GL_ARRAY_BUFFER, count * cardinality * sizeof(GLfloat), data, GL_STATIC_DRAW);

  glBindVertexArray(0);
}
