#include "Positionable.hpp"

#include <glm/gtc/matrix_transform.hpp>

Positionable::Positionable() :
  mTransform(glm::mat4(1.0f)) {}

void Positionable::translate(const glm::vec3 &direction) {
  mTransform = glm::translate(mTransform, direction);
}
