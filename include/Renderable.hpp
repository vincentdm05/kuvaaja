#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "Common.hpp"

#include "Positionable.hpp"

#include <vector>

class Material;

class Renderable : public Positionable {
public:
  Renderable();
  ~Renderable();

  void setVertexData(const float *data, unsigned int vertexCount) { setVaoData(data, mVertexBufferName, vertexCount, 3); mVertexCount = vertexCount; }
  void setNormalData(const std::vector<glm::vec3> &data) { setVaoData(data, mNormalBufferName); }
  void setColorData(const float *data, unsigned int pointCount) { setVaoData(data, mColorBufferName, pointCount, 3); }
  void setUvData(const float *data, unsigned int uvCount) { setVaoData(data, mUvBufferName, uvCount, 2); }
  void setMaterial(Material *material) { mMaterial = material; }

  void render() const;

  glm::mat4 modelMatrix() { return transform(); }
  Material *material() { return mMaterial; }

private:
  // VAO
  GLuint mVertexArrayName;
  // VBOs
  GLuint mVertexBufferName;
  GLuint mNormalBufferName;
  GLuint mColorBufferName;
  GLuint mUvBufferName;

  Material *mMaterial;

  unsigned int mVertexCount;

  void setVaoData(const GLfloat *data, GLuint &bufferName, unsigned int count, unsigned int cardinality);
  void setVaoData(const std::vector<glm::vec3> &data, GLuint &bufferName);
};

#endif // RENDERABLE_HPP
