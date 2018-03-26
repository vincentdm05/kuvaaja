#include "model/Model.hpp"

namespace model
{

Model::Model()
  : Model(true)
{}

Model::~Model()
{
  if (mIndices)
    mIndices->clear();
  if (mVertices)
    mVertices->clear();
  if (mNormals)
    mNormals->clear();
  if (mVertexColors)
    mVertexColors->clear();
  if (mUVs)
    mUVs->clear();

  delete mIndices;
  delete mVertices;
  delete mNormals;
  delete mVertexColors;
  delete mUVs;
}

Model::Model(bool initialise)
{
  if (initialise)
    init();
}

Model::Model(unsigned int vertexCount, unsigned int indexCount)
{
  init();
  mIndices->reserve(indexCount);
  mVertices->reserve(vertexCount);
  mNormals->reserve(vertexCount);
  mVertexColors->reserve(vertexCount);
  mUVs->reserve(vertexCount);
}

void Model::init()
{
  mIndices = new std::vector<unsigned int>();
  mVertices = new std::vector<glm::vec3>();
  mNormals = new std::vector<glm::vec3>();
  mVertexColors = new std::vector<glm::vec3>();
  mUVs = new std::vector<glm::vec2>();
}

} // namespace model
