#include "Control.hpp"

#include "Camera.hpp"
#include "Context.hpp"

Control::Control() :
  mContext(NULL),
  mCamera(NULL),
  mSpeed(0.1f),
  mPreviousCursorX(0.0),
  mPreviousCursorY(0.0) {}

void Control::setContext(Context *context) {
  mContext = context;

  if (mContext)
    mContext->cursorPosition(&mPreviousCursorX, &mPreviousCursorY);
}

void Control::updateCamera() {
  if (!mCamera || !mContext)
    return;

  // Get the signed percentage offset from center to border since the last call.
  double mouseX, mouseY;
  mContext->cursorPosition(&mouseX, &mouseY);
  mouseX -= mPreviousCursorX;
  mouseY -= mPreviousCursorY;
  mPreviousCursorX += mouseX;
  mPreviousCursorY += mouseY;
  mouseX /= mContext->windowWidth() / 2.0;
  mouseY /= mContext->windowHeight() / 2.0;

  if (mouseX != 0)
    mCamera->applyYaw(-mouseX * 180 * mSpeed);
  if (mouseY != 0)
    mCamera->applyPitch(-mouseY * 180 * mSpeed);
}
