#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include "Common.hpp"

#include <glm/gtc/matrix_transform.hpp>

class Positionable
{
public:
  Positionable();
  virtual ~Positionable() {}

  void scale(float x, float y, float z)
  {
    mScaling = glm::scale(mScaling, glm::vec3(x, y, z));
    mIsTransformDirty = true;
  }
  void rotate(float angle, float axisX, float axisY, float axisZ)
  {
    mRotation = glm::rotate(mRotation, angle, glm::vec3(axisX, axisY, axisZ));
    mIsTransformDirty = true;
  }
  void translate(float x, float y, float z)
  {
    mTranslation = glm::translate(mTranslation, glm::vec3(x, y, z));
    mIsTransformDirty = true;
  }

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
