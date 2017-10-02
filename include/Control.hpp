#ifndef CONTROL_HPP
#define CONTROL_HPP

class Camera;
class Context;

class Control {
public:
  Control();
  ~Control() {}

  void setContext(Context *context);
  void setCamera(Camera *camera) { mCamera = camera; }
  void updateCamera();

private:
  Context *mContext;
  Camera *mCamera;

  float mSpeed;
  double mPreviousCursorX;
  double mPreviousCursorY;

  bool mCtrlPressed;
  bool mCtrlToggled;
};

#endif // CONTROL_HPP
