#include "model/Model.hpp"

namespace model {

Model::Blueprints Model::cBlueprints;

Model::Model()
  : mIndices(nullptr)
  , mVertices(nullptr)
  , mNormals(nullptr)
  , mVertexColors(nullptr)
  , mUVs(nullptr)
{}

Model::Model(unsigned int vertexCount, unsigned int indexCount)
{
  mIndices = new std::vector<unsigned int>();
  mIndices->reserve(indexCount);
  mVertices = new std::vector<glm::vec3>();
  mVertices->reserve(vertexCount);
  mNormals = new std::vector<glm::vec3>();
  mNormals->reserve(vertexCount);
  mVertexColors = new std::vector<glm::vec3>();
  mVertexColors->reserve(vertexCount);
  mUVs = new std::vector<glm::vec2>();
  mUVs->reserve(vertexCount);
}

Model &Model::getBlueprint()
{
  const std::string &name = modelName();
  Blueprints::iterator it = cBlueprints.find(name);
  if (it == cBlueprints.end())
    cBlueprints[name] = makeBlueprint();
  return *cBlueprints[name];
}

void Model::initBlueprint()
{
  Model &blueprint = getBlueprint();
  mIndices = blueprint.mIndices;
  mVertices = blueprint.mVertices;
  mNormals = blueprint.mNormals;
  mVertexColors = blueprint.mVertexColors;
  mUVs = blueprint.mUVs;
}

void Model::releaseBlueprint()
{
  Blueprints::iterator pair = cBlueprints.find(modelName());
  assert(pair != cBlueprints.end() && "Could not find blueprint for release!");
  if (pair == cBlueprints.end())
    return;

  Model *blueprint = pair->second;
  blueprint->deleteBlueprint();
  cBlueprints.erase(pair);
  delete blueprint;
}

void Model::deleteBlueprint()
{
  mIndices->clear();
  mVertices->clear();
  mNormals->clear();
  mVertexColors->clear();
  mUVs->clear();

  delete mIndices;
  delete mVertices;
  delete mNormals;
  delete mVertexColors;
  delete mUVs;

  mIndices = nullptr;
  mVertices = nullptr;
  mNormals = nullptr;
  mVertexColors = nullptr;
  mUVs = nullptr;
}

} // namespace model
