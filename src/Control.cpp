#include "Control.hpp"

#include "Camera.hpp"
#include "Context.hpp"

Control::Control() :
  mContext(NULL),
  mCamera(NULL),
  mSpeed(0.1f),
  mPreviousCursorX(0.0),
  mPreviousCursorY(0.0),
  mCtrlPressed(false),
  mCtrlToggled(false) {}

void Control::setContext(Context *context) {
  mContext = context;

  if (mContext)
    mContext->cursorPosition(&mPreviousCursorX, &mPreviousCursorY);
}

void Control::updateCamera() {
  if (!mCamera || !mContext)
    return;

  float loopSpeed = mContext->loopTime() * 30.0f;
  float speed = mSpeed;
  if (mContext->keyPressed(KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT))
    speed *= 10.0f;

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

  // (x, z) camera plane movement
  if (mContext->keyPressed(KEY_RIGHT, KEY_D))
    mCamera->setPosition(mCamera->position() + mCamera->right() * loopSpeed * speed);
  if (mContext->keyPressed(KEY_LEFT, KEY_A))
    mCamera->setPosition(mCamera->position() - mCamera->right() * loopSpeed * speed);
  // Forward direction towards -z
  if (mContext->keyPressed(KEY_DOWN, KEY_S))
    mCamera->setPosition(mCamera->position() + mCamera->forward() * loopSpeed * speed);
  if (mContext->keyPressed(KEY_UP, KEY_W))
    mCamera->setPosition(mCamera->position() - mCamera->forward() * loopSpeed * speed);

  // Roll camera
  if (mContext->keyPressed(KEY_Q))
    mCamera->applyRoll(loopSpeed * 10 * speed);
  if (mContext->keyPressed(KEY_E))
    mCamera->applyRoll(-loopSpeed * 10 * speed);

  // Move camera up/down
  if (mContext->keyPressed(KEY_R))
    mCamera->setPosition(mCamera->position() + mCamera->up() * loopSpeed * speed);
  if (mContext->keyPressed(KEY_F))
    mCamera->setPosition(mCamera->position() - mCamera->up() * loopSpeed * speed);

  // Toggle to restrain camera up
  if (mContext->keyPressed(KEY_LEFT_CTRL, KEY_RIGHT_CTRL) && !mCtrlPressed) {
    mCtrlToggled = !mCtrlToggled;
    mCtrlPressed = true;
  } else if (!mContext->keyPressed(KEY_LEFT_CTRL, KEY_RIGHT_CTRL) && mCtrlPressed)
    mCtrlPressed = false;
  if (mCtrlToggled)
    mCamera->setUp(glm::vec3(0.0f, 1.0f, 0.0f));
}
