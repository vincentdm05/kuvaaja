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
  model::Model *mModel;

  void deleteBuffer(GLuint &bufferName);
  void resetBuffer(GLuint &bufferName);

  void setVaoIndices(const std::vector<unsigned int> &indices);
  template<class VecType> void setVaoData(const std::vector<VecType> &data, GLuint &bufferName);
};

template<class VecType>
void Renderable::setVaoData(const std::vector<VecType> &data, GLuint &bufferName)
{
  glBindVertexArray(mVertexArrayName);

  if (data.size() == 0)
  {
    deleteBuffer(bufferName);
  }
  else
  {
    resetBuffer(bufferName);
    glBindBuffer(GL_ARRAY_BUFFER, bufferName);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(VecType), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  glBindVertexArray(0);
}

#endif // RENDERABLE_HPP
