#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "Common.hpp"

#include "Positionable.hpp"

#include <vector>

class Material;

namespace model {
class Model;
}

class Renderable : public Positionable
{
public:
  Renderable();
  ~Renderable();

  void setVertexData(const float *data, unsigned int vertexCount) { setVaoData(data, mVertexBufferName, vertexCount, 3); mVertexCount = vertexCount; }
  void setNormalData(const std::vector<glm::vec3> &data) { setVaoData(data, mNormalBufferName); }
  void setColorData(const float *data, unsigned int pointCount) { setVaoData(data, mColorBufferName, pointCount, 3); }
  void setUvData(const float *data, unsigned int uvCount) { setVaoData(data, mUvBufferName, uvCount, 2); }
  void setMaterial(Material *material) { mMaterial = material; }
  void setModel(model::Model *model);

  void render() const;

  glm::mat4 modelMatrix() { return transform(); }
  Material *material() { return mMaterial; }

private:
  // VAO
  GLuint mVertexArrayName;
  // VBOs
  GLuint mIndexBufferName;
  GLuint mVertexBufferName;
  GLuint mNormalBufferName;
  GLuint mColorBufferName;
  GLuint mUvBufferName;

  Material *mMaterial;

  unsigned int mVertexCount;

  void setVaoData(const GLfloat *data, GLuint &bufferName, unsigned int count, unsigned int cardinality);
  void setVaoIndices(const std::vector<unsigned int> &indices);
  template<class VecType> void setVaoData(const std::vector<VecType> &data, GLuint &bufferName);
};

template<class VecType>
void Renderable::setVaoData(const std::vector<VecType> &data, GLuint &bufferName)
{
  glBindVertexArray(mVertexArrayName);

  if (glIsBuffer(bufferName) == GL_TRUE)
    glDeleteBuffers(1, &bufferName);

  glGenBuffers(1, &bufferName);
  glBindBuffer(GL_ARRAY_BUFFER, bufferName);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(VecType), &data[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

#endif // RENDERABLE_HPP
