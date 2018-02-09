#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Common.hpp"

class Light
{
public:
  Light();
  Light(float r, float g, float b, float intensity);
  virtual ~Light() {}

  void setEnabled(bool enabled) { mEnabled = enabled; }
  void setIntensity(float intensity) { mColorAndIntensity[3] = intensity; }
  void setColor(const glm::vec3 &color)
  {
    mColorAndIntensity[0] = color[0];
    mColorAndIntensity[1] = color[1];
    mColorAndIntensity[2] = color[2];
  }

  bool isEnabled() const { return mEnabled; }
  float intensity() const { return mColorAndIntensity[3]; }
  glm::vec3 color() const { return glm::vec3(mColorAndIntensity); }

  // Update data to currently bound program
  virtual void useAtLocation(GLuint location) const;
  inline virtual size_t locationSize() const { return 1; }

  // Subscript operator
  float &operator[](size_t i);
  float operator[](size_t i) const;

protected:
  bool mEnabled;
  glm::vec4 mColorAndIntensity;
};

#endif // LIGHT_HPP
