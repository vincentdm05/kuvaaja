#include "model/Quad.hpp"

namespace model {

const std::string Quad::cClassName = "Quad";
unsigned int Quad::cNumInstances = 0;

Quad::Quad()
{
  initBlueprint();
  cNumInstances++;
}

Quad::~Quad()
{
  cNumInstances--;
  if (cNumInstances == 1)
    releaseBlueprint();
}

Quad *Quad::makeBlueprint()
{
  return new Quad(4, 6);
}

Quad::Quad(unsigned int vertexCount, unsigned int indexCount)
  : Model(vertexCount, indexCount)
{
  glm::vec3 normal(0.0f, 0.0f, 1.0f);

  // First triangle
  // Bottom left vertex
  unsigned int vertexBLIndex = 0;
  mIndices->push_back(vertexBLIndex);
  mVertices->push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
  mNormals->push_back(normal);
  mVertexColors->push_back(glm::vec3(0.0f, 0.0, 0.5f));
  mUVs->push_back(glm::vec2(0.0f, 0.0f));

  // Top right vertex
  unsigned int vertexTRIndex = vertexBLIndex + 1;
  mIndices->push_back(vertexTRIndex);
  mVertices->push_back(glm::vec3(0.5f, 0.5f, 0.0f));
  mNormals->push_back(normal);
  mVertexColors->push_back(glm::vec3(1.0f, 1.0f, 0.5));
  mUVs->push_back(glm::vec2(1.0f, 1.0f));

  // Top left vertex
  unsigned int vertexTLIndex = vertexTRIndex + 1;
  mIndices->push_back(vertexTLIndex);
  mVertices->push_back(glm::vec3(-0.5f, 0.5f, 0.0f));
  mNormals->push_back(normal);
  mVertexColors->push_back(glm::vec3(0.0f, 1.0f, 0.5));
  mUVs->push_back(glm::vec2(0.0f, 1.0f));

  // Second triangle
  // Top right and bottom left
  mIndices->push_back(vertexTRIndex);
  mIndices->push_back(vertexBLIndex);

  // Bottom right vertex
  unsigned int vertexBRIndex = vertexTLIndex + 1;
  mIndices->push_back(vertexBRIndex);
  mVertices->push_back(glm::vec3(0.5f, -0.5f, 0.0f));
  mNormals->push_back(normal);
  mVertexColors->push_back(glm::vec3(1.0f, 0.0f, 0.5));
  mUVs->push_back(glm::vec2(1.0f, 0.0f));

  cNumInstances++;
}

} // namespace model
