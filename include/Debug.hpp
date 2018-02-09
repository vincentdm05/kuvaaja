#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "Common.hpp"

#include <iostream>

void printOpenGlErrors()
{
  GLenum err_code = glGetError();
  while( GL_NO_ERROR != err_code )
  {
    std::cerr << "OpenGL Error: 0x" << std::hex << err_code << std::endl;
    err_code = glGetError();
  }
}

#endif // DEBUG_HPP
