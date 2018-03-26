#include "model/Triangle.hpp"

namespace model
{

const std::string Triangle::cClassName = "Triangle";

Triangle::Triangle()
{
  acquireBlueprint();
}

Triangle::~Triangle()
{
  releaseBlueprint();
}

Triangle *Triangle::makeBlueprint() const
{
  return new Triangle(3);
}

Triangle::Triangle(unsigned int vertexCount)
  : PrimitiveModel(vertexCount)
{
  float twoPiOver3 = 3.14159265359f * 2.0f / 3.0f;
  float cosPiOver3 = cos(twoPiOver3);
  float sinPiOver3 = sin(twoPiOver3);
  glm::mat3x3 rot(1.0f);
  rot[0][0] = cosPiOver3; rot[1][0] = -sinPiOver3;
  rot[0][1] = sinPiOver3; rot[1][1] = cosPiOver3;

  float sideLength = 1.0f;
  float armLength = sqrt(0.75f * sideLength * sideLength) * 2.0f / 3.0f;
  glm::vec3 direction(0.0f, armLength, 0.0f);
  glm::vec3 normal(0.0f, 0.0f, 1.0f);
  for (uint8_t v = 0; v < 3; v++)
  {
    mVertices->push_back(direction);
    mNormals->push_back(normal);
    glm::vec3 color(sideLength * 0.5 + direction.x, armLength * 0.5f + direction.y, 0.5f);
    mVertexColors->push_back(color);
    mUVs->push_back(glm::vec2(color));

    direction = rot * direction;
  }
}

} // namespace model
