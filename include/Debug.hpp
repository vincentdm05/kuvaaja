#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "Common.hpp"

#include <iostream>
#include <string>

static void printOpenGlErrors(const std::string &context, bool verbose = false)
{
#ifdef KUVAAJA_DEBUG
  GLenum err_code = glGetError();
  while( GL_NO_ERROR != err_code )
  {
    std::string info = "";
    if (verbose)
    {
      info = " -- ";
      switch (err_code) {
      case GL_INVALID_ENUM:
        info += "Invalid enum: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
      case GL_INVALID_VALUE:
        info += "Invalid value: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
      case GL_INVALID_OPERATION:
        info += "Invalid operation: An operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        info += "Invalid framebuffer operation: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
      case GL_OUT_OF_MEMORY:
        info += "Out of memory: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
        break;
      case GL_STACK_UNDERFLOW:
        info += "Stack underflow: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
        break;
      case GL_STACK_OVERFLOW:
        info += "Stack overflow: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
        break;
      default:
        info += "Unrecognised error code.";
        break;
      }
    }
    std::cerr << "OpenGL Error: 0x" << std::hex << err_code << " in " << context << info << std::endl;
    err_code = glGetError();
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
