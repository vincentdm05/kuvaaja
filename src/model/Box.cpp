#include "model/Box.hpp"

namespace model {

const std::string Box::cClassName = "Box";
unsigned int Box::cNumInstances = 0;

Box::Box()
{
  initBlueprint();
  cNumInstances++;
}

Box::~Box()
{
  cNumInstances--;
  if (cNumInstances == 1)
    releaseBlueprint();
}

Box *Box::makeBlueprint()
{
  return new Box(36);
}

Box::Box(unsigned int vertexCount)
  : Model(vertexCount)
{
  float l = 1.0f; // Side length
  l *= 0.5f; // Halve length to start from center

  float left = -l;
  float right = l;
  float bottom = -l;
  float top = l;
  float front = l;
  float back = -l;

  // 6 sides, 1 normal each
  const glm::vec3 normals[6] =
  {
    glm::vec3(0.0f, 0.0f, front / l),
    glm::vec3(right / l, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, back / l),
    glm::vec3(left / l, 0.0f, 0.0f),
    glm::vec3(0.0f, top / l, 0.0f),
    glm::vec3(0.0f, bottom / l, 1.0f)
  };

  // 8 corners of the cube
  const glm::vec3 corners[8] =
  {
    glm::vec3(left, bottom, front),  // 0
    glm::vec3(right, top, front),    // 1
    glm::vec3(left, top, front),     // 2
    glm::vec3(right, bottom, front), // 3
    glm::vec3(right, bottom, back),  // 4
    glm::vec3(left, top, back),      // 5
    glm::vec3(right, top, back),     // 6
    glm::vec3(left, bottom, back)    // 7
  };

  // Vertices arranged in quads
  const glm::vec3 vertices[24] =
  {
    corners[0], corners[1], corners[2], corners[3], // front
    corners[3], corners[6], corners[1], corners[4], // right
    corners[4], corners[5], corners[6], corners[7], // back
    corners[7], corners[2], corners[5], corners[0], // left
    corners[2], corners[6], corners[5], corners[1], // top
    corners[3], corners[7], corners[4], corners[0]  // bottom
  };

  // TODO: choose a UV pattern

  unsigned int vertexIndex = 0;
  for (unsigned short i = 0; i < 6; i++)
  {
    glm::vec3 normal = normals[i];

    // First triangle
    // Bottom left vertex
    unsigned int vertexBLIndex = vertexIndex;
    mIndices->push_back(vertexBLIndex);
    glm::vec3 vertex = vertices[i * 4];
    mVertices->push_back(vertex);
    mNormals->push_back(normal);
    mVertexColors->push_back((vertex + glm::vec3(l)) * glm::vec3(1.0f / (2.0f * l)));
    mUVs->push_back(glm::vec2(0.0f, 0.0f));

    // Top right vertex
    unsigned int vertexTRIndex = vertexBLIndex + 1;
    mIndices->push_back(vertexTRIndex);
    vertex = vertices[i * 4 + 1];
    mVertices->push_back(vertex);
    mNormals->push_back(normal);
    mVertexColors->push_back((vertex + glm::vec3(l)) * glm::vec3(1.0f / (2.0f * l)));
    mUVs->push_back(glm::vec2(1.0f, 1.0f));

    // Top left vertex
    unsigned int vertexTLIndex = vertexTRIndex + 1;
    mIndices->push_back(vertexTLIndex);
    vertex = vertices[i * 4 + 2];
    mVertices->push_back(vertex);
    mNormals->push_back(normal);
    mVertexColors->push_back((vertex + glm::vec3(l)) * glm::vec3(1.0f / (2.0f * l)));
    mUVs->push_back(glm::vec2(0.0f, 1.0f));

    // Second triangle
    // Top right and bottom left
    mIndices->push_back(vertexTRIndex);
    mIndices->push_back(vertexBLIndex);

    // Bottom right vertex
    unsigned int vertexBRIndex = vertexTLIndex + 1;
    mIndices->push_back(vertexBRIndex);
    vertex = vertices[i * 4 + 3];
    mVertices->push_back(vertex);
    mNormals->push_back(normal);
    mVertexColors->push_back((vertex + glm::vec3(l)) * glm::vec3(1.0f / (2.0f * l)));
    mUVs->push_back(glm::vec2(1.0f, 0.0f));

    vertexIndex = vertexBRIndex + 1;
  }

  cNumInstances++;
}

} // namespace model
