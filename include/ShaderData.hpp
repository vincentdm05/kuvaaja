#ifndef SHADER_DATA_HPP
#define SHADER_DATA_HPP

#include "Common.hpp"

class ShaderProgram;

enum UniformType
{
  MAT_MODEL_VIEW_PROJECTION,  // Necessary for vertex data
  MAT_INVERSE_TRANSPOSE_MODEL,  // Necessary for normal data
  TEXTURE,
  AMBIENT_LIGHT,
  POINT_LIGHTS,
  DIRECTIONAL_LIGHTS,
  SPOT_LIGHTS,
  UNIFORM_TYPE_COUNT  // Not a type
};

enum UniformBuffer
{
  LIGHTS,
  UBO_COUNT
};

// Layout definitions
struct ShaderLightProperties  // TODO: replace with colorAndIntensity?
{
  glm::vec3 color;
  float intensity;
};

struct ShaderPointLight
{
  ShaderLightProperties props;
  glm::vec4 position;
};

struct ShaderDirectionalLight
{
  ShaderLightProperties props;
  glm::vec4 direction;
};

struct ShaderSpotLight
{
  ShaderLightProperties props;
  glm::vec4 position;
  glm::vec4 direction;
};

// For now, fix cap light number to a low amount
const size_t MAX_LIGHTS = 8;

struct ShaderLights
{
  ShaderPointLight pointLights[MAX_LIGHTS];
  ShaderDirectionalLight directionalLights[MAX_LIGHTS];
  ShaderSpotLight spotLights[MAX_LIGHTS];
};

#endif // SHADER_DATA_HPP
