#include "Light.hpp"

Light::Light() :
  Light(1.0f, 1.0f, 1.0f, 1.0f) {}

Light::Light(float r, float g, float b, float intensity) :
  mEnabled(true),
  mColorAndIntensity(glm::vec4(r, g, b, intensity)) {}

void Light::useAtLocation(GLuint location) const {
  glUniform4fv(location, 1, &mColorAndIntensity[0]);
}

float &Light::operator[](size_t i) {
  assert(i <= 3 && "Trying to access light out of bounds.");
  return mColorAndIntensity[i];
}

float Light::operator[](size_t i) const {
  assert(i <= 3 && "Trying to access light out of bounds.");
  return mColorAndIntensity[i];
}
