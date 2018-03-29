#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "Common.hpp"

#include <iostream>
#include <string>

enum GlErrorType
{
  InvalidEnum = 1,
  InvalidValue = InvalidEnum << 1,
  InvalidOperation = InvalidValue << 1,
  InvalidFramebufferOperation = InvalidOperation << 1,
  OutOfMemory = InvalidFramebufferOperation << 1,
  StackUnderflow = OutOfMemory << 1,
  StackOverflow = StackUnderflow << 1
};

static void printOpenGlErrors(const std::string &context, bool onlyOnce = true, bool verbose = false)
{
#ifdef KUVAAJA_DEBUG
  static uint32_t errorMask = 0;
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string info = "";
    bool ignoreError = false;

    switch (errorCode) {
    case GL_INVALID_ENUM:
      if (verbose)
        info = "Invalid enum: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
      ignoreError |= (onlyOnce && (errorMask & InvalidEnum));
      errorMask |= InvalidEnum;
      break;
    case GL_INVALID_VALUE:
      if (verbose)
        info = "Invalid value: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
      ignoreError |= (onlyOnce && (errorMask & InvalidValue));
      errorMask |= InvalidValue;
      break;
    case GL_INVALID_OPERATION:
      if (verbose)
        info = "Invalid operation: An operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
      ignoreError |= (onlyOnce && (errorMask & InvalidOperation));
      errorMask |= InvalidOperation;
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      if (verbose)
        info = "Invalid framebuffer operation: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
      ignoreError |= (onlyOnce && (errorMask & InvalidFramebufferOperation));
      errorMask |= InvalidFramebufferOperation;
      break;
    case GL_OUT_OF_MEMORY:
      if (verbose)
        info = "Out of memory: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
      ignoreError |= (onlyOnce && (errorMask & OutOfMemory));
      errorMask |= OutOfMemory;
      break;
    case GL_STACK_UNDERFLOW:
      if (verbose)
        info = "Stack underflow: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
      ignoreError |= (onlyOnce && (errorMask & StackUnderflow));
      errorMask |= StackUnderflow;
      break;
    case GL_STACK_OVERFLOW:
      if (verbose)
        info = "Stack overflow: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
      ignoreError |= (onlyOnce && (errorMask & StackOverflow));
      errorMask |= StackOverflow;
      break;
    default:
      info = "Unrecognised error code.";
      break;
    }

    if (info.size() > 0)
      info = " -- " + info;

    if (!ignoreError)
      std::cerr << "OpenGL Error: 0x" << std::hex << errorCode << " in " << context << info << std::endl;
  }
#endif
}

static void printOpenGlState(const std::string &context)
{
  std::cout << context << std::endl;
  GLint dataInt;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &dataInt);
  std::cout << "Active texture unit: " << dataInt << std::endl;
  glGetIntegerv(GL_TEXTURE_BINDING_1D, &dataInt);
  std::cout << "Currently bound 1D texture name: " << dataInt << std::endl;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &dataInt);
  std::cout << "Currently bound 2D texture name: " << dataInt << std::endl;
  glGetIntegerv(GL_TEXTURE_BINDING_3D, &dataInt);
  std::cout << "Currently bound 3D texture name: " << dataInt << std::endl;
  glGetIntegerv(GL_TEXTURE_BINDING_BUFFER, &dataInt);
  std::cout << "Currently bound texture buffer name: " << dataInt << std::endl;
  glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &dataInt);
  std::cout << "Currently bound cubemap name: " << dataInt << std::endl;
  glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &dataInt);
  std::cout << "Currently bound uniform buffer name: " << dataInt << std::endl;
}

#endif // DEBUG_HPP
