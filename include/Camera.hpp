#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Common.hpp"

class Camera {
public:
  Camera();
  ~Camera() {}

  void setPosition(const glm::vec3 &position) { mPosition = position; mIsViewDirty = true; }
  void setDirection(const glm::vec3 &direction) { mDirection = direction; mIsViewDirty = true; }
  void setUp(const glm::vec3 &up) { mUp = up; mIsViewDirty = true; }
  void setFoV(float fieldOfView) { mFoV = glm::radians(fieldOfView); mIsProjectionDirty = true; }
  void setAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; mIsProjectionDirty = true; }
  void setNear(float near) { mNear = near; mIsProjectionDirty = true; }
  void setFar(float far) { mFar = far; mIsProjectionDirty = true; }

  void applyYaw(float angle);
  void applyPitch(float angle);
  void applyRoll(float angle);

  glm::vec3 right();
  const glm::vec3 &up();
  glm::vec3 forward();
  const glm::vec3 &position() { return mPosition; }

  const glm::mat4 &viewMatrix();
  const glm::mat4 &projectionMatrix();

private:
  glm::vec3 mPosition;
  glm::vec3 mDirection;
  glm::vec3 mUp;
  glm::mat4 mView;
  bool mIsViewDirty;

  float mFoV;
  float mAspectRatio;
  float mNear;
  float mFar;
  glm::mat4 mProjection;
  bool mIsProjectionDirty;

  void rebuildViewMatrix();
  void rotateView(float angle, const glm::vec3 &axis);
};

#endif // CAMERA_HPP
