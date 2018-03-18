#include "Positionable.hpp"

Positionable::Positionable()
  : mIsTransformDirty(true)
  , mTransform(glm::mat4(1.0f))
  , mScaling(glm::mat4(1.0f))
  , mRotation(glm::mat4(1.0f))
  , mTranslation(glm::mat4(1.0f))
{}

const glm::mat4 &Positionable::transform()
{
  if (mIsTransformDirty)
  {
    mTransform = mTranslation * mRotation * mScaling;
    mIsTransformDirty = false;
  }

  return mTransform;
}
