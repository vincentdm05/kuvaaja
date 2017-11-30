#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() :
  mDirection(glm::vec4(0.0f, -1.0f, 0.0f, 1.0f)) {}

void DirectionalLight::useAtLocation(GLuint location) const {
  Light::useAtLocation(location);
  location += Light::locationSize();
  glUniform4fv(location, 1, &mDirection[0]);
}
