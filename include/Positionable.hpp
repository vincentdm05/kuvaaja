#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include <glm/glm.hpp>

class Positionable {
public:
  Positionable();
  ~Positionable() {}

protected:
  void translate(const glm::vec3 &direction);
  glm::mat4 transform() const;

private:
  glm::mat4 mTransform;
};

#endif // POSITIONABLE_HPP
