#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
  : mPosition(glm::vec3(0.0f, 0.0f, 1.0f))
  , mDirection(glm::vec3(0.0f, 0.0f, -1.0f))
  , mUp(glm::vec3(0.0f))
  , mView(glm::mat4(1.0f))
  , mIsViewDirty(true)
{}

void Camera::applyYaw(float angle)
{
  rotateView(glm::radians(angle), up());
}

void Camera::applyPitch(float angle)
{
  rotateView(glm::radians(angle), right());
}

void Camera::applyRoll(float angle)
{
  rotateView(glm::radians(angle), forward());
}

glm::vec3 Camera::right()
{
  glm::mat4 m = viewMatrix();
  return glm::vec3(m[0][0], m[1][0], m[2][0]);
}

const glm::vec3 &Camera::up()
{
  if (mIsViewDirty)
  {
    rebuildViewMatrix();
    mIsViewDirty = false;
  }

  return mUp;
}

glm::vec3 Camera::forward()
{
  glm::mat4 m = viewMatrix();
  return glm::vec3(m[0][2], m[1][2], m[2][2]);
}

const glm::mat4 &Camera::viewMatrix()
{
  if (mIsViewDirty)
  {
    rebuildViewMatrix();
    mIsViewDirty = false;
  }

  return mView;
}

const glm::mat4 &Camera::projectionMatrix()
{
  if (mIsProjectionDirty)
  {
    mProjection = glm::perspective(mFoV, mAspectRatio, mNear, mFar);
    mIsProjectionDirty = false;
  }

  return mProjection;
}

void Camera::rebuildViewMatrix()
{
  mView = glm::lookAt(mPosition, mPosition + mDirection, mUp);
  mUp = glm::vec3(mView[0][1], mView[1][1], mView[2][1]);
}

void Camera::rotateView(float angle, const glm::vec3 &axis)
{
  glm::vec4 v = glm::vec4(mDirection, 0.0f);
  glm::vec4 u = glm::vec4(mUp, 0.0f);
  glm::mat4 r = glm::rotate(glm::mat4(1.0f), angle, axis);
  glm::vec4 newDirection = r * v;
  glm::vec4 newUp = r * u;

  mDirection[0] = newDirection.x;
  mDirection[1] = newDirection.y;
  mDirection[2] = newDirection.z;

  mUp[0] = newUp.x;
  mUp[1] = newUp.y;
  mUp[2] = newUp.z;

  mIsViewDirty = true;
}
