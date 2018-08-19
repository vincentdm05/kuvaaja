#ifndef MODEL_HPP
#define MODEL_HPP

#include "Common.hpp"

#include <vector>

namespace model
{

class Model
{
public:
  Model();
  Model(const std::string &path);
  virtual ~Model();

  unsigned int vertexCount() const { return mVertices ? mVertices->size() : 0; }
  unsigned int indexCount() const { return mIndices ? mIndices->size() : 0; }
  const std::vector<unsigned int> &indices() const { return *mIndices; }
  const std::vector<glm::vec3> &vertices() const { return *mVertices; }
  const std::vector<glm::vec3> &normals() const { return *mNormals; }
  const std::vector<glm::vec3> &vertexColors() const { return *mVertexColors; }
  const std::vector<glm::vec2> &uvs() const { return *mUVs; }

  bool loadFromFile(const std::string &path);

protected:
  Model(bool initialise);
  Model(unsigned int vertexCount, unsigned int indexCount);

  std::vector<unsigned int> *mIndices;
  std::vector<glm::vec3> *mVertices;
  std::vector<glm::vec3> *mNormals;
  std::vector<glm::vec3> *mVertexColors;
  std::vector<glm::vec2> *mUVs;

private:
  void init();
  void reset();
  glm::vec3 computeNormal(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2) const;
};

} // namespace model

#endif // MODEL_HPP
