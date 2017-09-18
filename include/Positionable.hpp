#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Positionable {
public:
  Positionable();
  ~Positionable() {}

  void scale(const glm::vec3 &scale) { mScaling = glm::scale(mScaling, scale); mIsTransformDirty = true; }
  void rotate(float angle, const glm::vec3 &axis) { mRotation = glm::rotate(mRotation, angle, axis); mIsTransformDirty = true; }
  void translate(const glm::vec3 &direction) { mTranslation = glm::translate(mTranslation, direction); mIsTransformDirty = true; }

protected:
  const glm::mat4 &transform();

private:
  bool mIsTransformDirty;

  glm::mat4 mTransform;
  glm::mat4 mScaling;
  glm::mat4 mRotation;
  glm::mat4 mTranslation;
};

#endif // POSITIONABLE_HPP
