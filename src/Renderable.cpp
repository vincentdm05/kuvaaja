#include "Renderable.hpp"

#include "Material.hpp"
#include "model/Model.hpp"

Renderable::Renderable()
  : mVertexArrayName(0)
  , mIndexBufferName(0)
  , mVertexBufferName(0)
  , mNormalBufferName(0)
  , mColorBufferName(0)
  , mUvBufferName(0)
  , mMaterial(nullptr)
  , mModel(nullptr)
{
  glGenVertexArrays(1, &mVertexArrayName);
}

Renderable::~Renderable()
{
  glDeleteBuffers(1, &mIndexBufferName);
  glDeleteBuffers(1, &mVertexBufferName);
  glDeleteBuffers(1, &mNormalBufferName);
  glDeleteBuffers(1, &mColorBufferName);
  glDeleteBuffers(1, &mUvBufferName);
  glDeleteVertexArrays(1, &mVertexArrayName);
}

void Renderable::setModel(model::Model *model)
{
  mModel = model;
  setVaoIndices(mModel->indices());
  setVaoData(mModel->vertices(), mVertexBufferName);
  setVaoData(mModel->normals(), mNormalBufferName);
  setVaoData(mModel->vertexColors(), mColorBufferName);
  setVaoData(mModel->uvs(), mUvBufferName);
}

void Renderable::render() const
{
  if (mVertexArrayName == 0)
    return;

  if (!mMaterial)
    return;

  if (!mModel || mModel->vertexCount() == 0)
    return;

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

  if (mIndexBufferName != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferName);
    glDrawElements(GL_TRIANGLES, mModel->indexCount(), GL_UNSIGNED_INT, (void*)0);
  }
  else
  {
    glDrawArrays(GL_TRIANGLES, 0, mModel->vertexCount());
  }

  glDisableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Renderable::deleteBuffer(GLuint &bufferName)
{
  if (glIsBuffer(bufferName) == GL_TRUE)
    glDeleteBuffers(1, &bufferName);

  bufferName = 0;
}

void Renderable::resetBuffer(GLuint &bufferName)
{
  deleteBuffer(bufferName);
  glGenBuffers(1, &bufferName);
}

void Renderable::setVaoIndices(const std::vector<unsigned int> &indices)
{
  glBindVertexArray(mVertexArrayName);

  if (indices.size() == 0)
  {
    deleteBuffer(mIndexBufferName);
  }
  else
  {
    resetBuffer(mIndexBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferName);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  glBindVertexArray(0);
}
