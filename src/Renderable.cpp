#include "Renderable.hpp"

#include "Debug.hpp"
#include "Material.hpp"

Renderable::Renderable()
  : mVertexArrayName(0)
  , mVertexBufferName(0)
  , mNormalBufferName(0)
  , mColorBufferName(0)
  , mUvBufferName(0)
  , mMaterial(NULL)
  , mVertexCount(0)
{
  glGenVertexArrays(1, &mVertexArrayName);
}

Renderable::~Renderable()
{
  glDeleteBuffers(1, &mVertexBufferName);
  glDeleteBuffers(1, &mNormalBufferName);
  glDeleteBuffers(1, &mColorBufferName);
  glDeleteBuffers(1, &mUvBufferName);
  glDeleteVertexArrays(1, &mVertexArrayName);
}

void Renderable::render() const
{
  glBindVertexArray(mVertexArrayName);

  // Draw data
  GLuint attribArrayNumber = 0;
  glEnableVertexAttribArray(attribArrayNumber);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferName);
  glVertexAttribPointer(attribArrayNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  attribArrayNumber++;
  glEnableVertexAttribArray(attribArrayNumber);
  glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferName);
  glVertexAttribPointer(attribArrayNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  if (mColorBufferName != 0)
  {
    attribArrayNumber++;
    glEnableVertexAttribArray(attribArrayNumber);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBufferName);
    glVertexAttribPointer(attribArrayNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  }

  if (mUvBufferName != 0)
  {
    attribArrayNumber++;
    glEnableVertexAttribArray(attribArrayNumber);
    glBindBuffer(GL_ARRAY_BUFFER, mUvBufferName);
    glVertexAttribPointer(attribArrayNumber, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  }

  glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
  glDisableVertexAttribArray(0);

  glBindVertexArray(0);

  printOpenGlErrors("Renderable::render()");
}

void Renderable::setVaoData(const GLfloat *data, GLuint &bufferName, unsigned int count, unsigned int cardinality)
{
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(bufferName) == GL_TRUE)
    glDeleteBuffers(1, &bufferName);

  glGenBuffers(1, &bufferName);
  glBindBuffer(GL_ARRAY_BUFFER, bufferName);
  glBufferData(GL_ARRAY_BUFFER, count * cardinality * sizeof(GLfloat), data, GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void Renderable::setVaoData(const std::vector<glm::vec3> &data, GLuint &bufferName)
{
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(bufferName) == GL_TRUE)
    glDeleteBuffers(1, &bufferName);

  glGenBuffers(1, &bufferName);
  glBindBuffer(GL_ARRAY_BUFFER, bufferName);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}
