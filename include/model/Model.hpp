#ifndef MODEL_HPP
#define MODEL_HPP

#include "Common.hpp"

#include <map>
#include <string>
#include <vector>

namespace model {

class Model
{
public:
  unsigned int vertexCount() const { return mVertices ? mVertices->size() : 0; }
  unsigned int indexCount() const { return mIndices ? mIndices->size() : 0; }
  const std::vector<unsigned int> &indices() const { return *mIndices; }
  const std::vector<glm::vec3> &vertices() const { return *mVertices; }
  const std::vector<glm::vec3> &normals() const { return *mNormals; }
  const std::vector<glm::vec3> &vertexColors() const { return *mVertexColors; }
  const std::vector<glm::vec2> &uvs() const { return *mUVs; }

protected:
  Model();
  Model(unsigned int vertexCount, unsigned int indexCount = 0); // Blueprint ctr
  virtual ~Model() {}

  std::vector<unsigned int> *mIndices;
  std::vector<glm::vec3> *mVertices;
  std::vector<glm::vec3> *mNormals;
  std::vector<glm::vec3> *mVertexColors;
  std::vector<glm::vec2> *mUVs;

  Model &getBlueprint();
  void initBlueprint();
  void releaseBlueprint();

  virtual const std::string &modelName() const = 0;
  virtual Model *makeBlueprint() = 0;
  void deleteBlueprint();

private:

  typedef std::map<std::string, Model*> Blueprints;
  static Blueprints cBlueprints;
};

} // namespace model

#endif // MODEL_HPP
