#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
  mPosition(glm::vec3(1.0f, 0.0f, 1.0f)),
  mLookingAt(glm::vec3(0.0f)),
  mUp(glm::vec3(0.0f)),
  mView(glm::mat4(1.0f)),
  mIsViewDirty(true) {}

glm::mat4 Camera::viewMatrix() {
  if (mIsViewDirty) {
    mView = glm::lookAt(mPosition, mLookingAt, mUp);
    mIsViewDirty = false;
  }

  return mView;
}

glm::mat4 Camera::projectionMatrix() {
  if (mIsProjectionDirty) {
    mProjection = glm::perspective(mFoV, mAspectRatio, mNear, mFar);
    mIsProjectionDirty = false;
  }

  return mProjection;
}
