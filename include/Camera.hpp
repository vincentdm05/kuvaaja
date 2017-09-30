#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
public:
  Camera();
  ~Camera() {}

  void setPosition(float x, float y, float z) { mPosition = glm::vec3(x, y, z); mIsViewDirty = true; }
  void setLookingAt(float x, float y, float z) { mDirection = glm::vec3(x, y, z) - mPosition; mIsViewDirty = true; }
  void setUp(float x, float y, float z) { mUp = glm::vec3(x, y, z); mIsViewDirty = true; }
  void setFoV(float fieldOfView) { mFoV = glm::radians(fieldOfView); mIsProjectionDirty = true; }
  void setAspectRatio(float aspectRatio) { mAspectRatio = aspectRatio; mIsProjectionDirty = true; }
  void setNear(float near) { mNear = near; mIsProjectionDirty = true; }
  void setFar(float far) { mFar = far; mIsProjectionDirty = true; }

  void applyYaw(float angle);
  void applyPitch(float angle);

  glm::mat4 viewMatrix();
  glm::mat4 projectionMatrix();

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

  glm::vec3 up();
  glm::vec3 right();

  void rotateView(float angle, const glm::vec3 &axis);
};

#endif // CAMERA_HPP
