#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
  mPosition(glm::vec3(0.0f, 0.0f, 1.0f)),
  mDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
  mUp(glm::vec3(0.0f)),
  mView(glm::mat4(1.0f)),
  mIsViewDirty(true) {}

void Camera::applyYaw(float angle) {
  rotateView(glm::radians(angle), up());
}

void Camera::applyPitch(float angle) {
  rotateView(glm::radians(angle), right());
}

glm::mat4 Camera::viewMatrix() {
  if (mIsViewDirty) {
    mView = glm::lookAt(mPosition, mPosition + mDirection, mUp);
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

glm::vec3 Camera::up() {
  glm::mat4 m = viewMatrix();
  return glm::vec3(m[0][1], m[1][1], m[2][1]);
}

glm::vec3 Camera::right() {
  glm::mat4 m = viewMatrix();
  return glm::vec3(m[0][0], m[1][0], m[2][0]);
}

void Camera::rotateView(float angle, const glm::vec3 &axis) {
  glm::vec4 v = glm::vec4(mDirection, 0.0f);
  glm::mat4 r = glm::rotate(glm::mat4(1.0f), angle, axis);
  glm::vec4 newDirection = r * v;

  mDirection[0] = newDirection.x;
  mDirection[1] = newDirection.y;
  mDirection[2] = newDirection.z;

  mIsViewDirty = true;
}
