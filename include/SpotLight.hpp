#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "Common.hpp"

#include "Light.hpp"

class SpotLight : public Light
{
public:
  SpotLight();
  ~SpotLight() {}

  void setDirection(const glm::vec3 &direction) { mDirection = direction; }
  void setPosition(const glm::vec3 &position) { mPosition = position; }

  const glm::vec3 &direction() { return mDirection; }
  const glm::vec3 &position() { return mPosition; }

private:
  glm::vec3 mDirection;
  glm::vec3 mPosition;
};

#endif // SPOT_LIGHT_HPP
