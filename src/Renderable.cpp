#include "Renderable.hpp"

#include "Material.hpp"
#include "ShaderDataManager.hpp"

#include <iostream>

Renderable::Renderable()
  : mVertexArrayName(0)
  , mVertexBufferName(0)
  , mNormalBufferName(0)
  , mColorBufferName(0)
  , mUvBufferName(0)
  , mMaterial(NULL)
  , mVertexCount(0)
  , mUniformDeclarationBuffer()
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

void Renderable::setVertexData(const float *data, unsigned int vertexCount)
{
  setVaoData(data, mVertexBufferName, vertexCount, 3);
  mVertexCount = vertexCount;
  mUniformDeclarationBuffer.push_back(UniformType::MAT_MODEL_VIEW_PROJECTION);
}

void Renderable::setNormalData(const std::vector<glm::vec3> &data)
{
  setVaoData(data, mNormalBufferName);
  mUniformDeclarationBuffer.push_back(UniformType::MAT_INVERSE_TRANSPOSE_MODEL);
}

void Renderable::render() const
{
  if (!unbufferUniformDeclarations())
  {
    std::cerr << "Unable to declare uniforms, maybe a material wasn't set?" << std::endl;
    return;
  }

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
}

bool Renderable::unbufferUniformDeclarations() const
{
  if (mUniformDeclarationBuffer.empty())
    return true;

  if (!mMaterial)
    return false;

  ShaderProgram *program = mMaterial->shaderProgram();
  if (!program)
    return false;

  for (UniformType &u : mUniformDeclarationBuffer)
  {
    if (!ShaderDataManager::shaderDataManagerReference().declareUniform(program, u))
      return false;
  }
  mUniformDeclarationBuffer.clear();

  return true;
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
