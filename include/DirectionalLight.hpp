#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Common.hpp"

#include "Light.hpp"

class DirectionalLight : public Light {
public:
  DirectionalLight();
  ~DirectionalLight() {}

  void setDirection(float x, float y, float z) { mDirection = glm::vec4(x, y, z, 1.0f); }
  void setDirection(const glm::vec3 &direction) { mDirection = glm::vec4(direction, 1.0f); }

  const glm::vec4 &direction() { return mDirection; }

  virtual void useAtLocation(GLuint location) const;
  inline virtual size_t locationSize() const {
    return Light::locationSize() + 1;
  }

private:
  glm::vec4 mDirection;
};

#endif // DIRECTIONAL_LIGHT_HPP
