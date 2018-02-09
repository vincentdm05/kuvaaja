#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Common.hpp"

#include "Light.hpp"

class PointLight : public Light
{
public:
  PointLight();
  ~PointLight() {}

  void setPosition(const glm::vec3 &position) { mPosition = position; }

  const glm::vec3 &position() { return mPosition; }

private:
  glm::vec3 mPosition;
};

#endif // POINT_LIGHT_HPP
