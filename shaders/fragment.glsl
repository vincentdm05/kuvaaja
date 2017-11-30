#version 330 core

in vec3 fragmentColor;
in vec2 texUV;

out vec3 color;

uniform vec4 ambientLight = vec4(1.0, 0.0, 0.0, 1.0);

const int MAX_LIGHTS = 8;

struct LightProperties {
  vec3 color;
  float intensity;
};
struct PointLight {
  LightProperties props;
  vec4 position;
};
struct DirectionalLight {
  LightProperties props;
  vec4 direction;
};
struct SpotLight {
  LightProperties props;
  vec4 position;
  vec4 direction;
};

uniform PointLight pointLights[MAX_LIGHTS];
uniform DirectionalLight directionalLight[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];

uniform sampler2D textureSampler;

void main() {
  // Ambient light
  color = ambientLight.xyz * ambientLight.w;

  // Point lights
  for (int i = 0; i < MAX_LIGHTS; i++) {
    PointLight light = pointLights[i];
    if (light.props.intensity == 0.0)
      continue;
  }

  // Directional lights
  for (int i = 0; i < MAX_LIGHTS; i++) {
    DirectionalLight light = directionalLight[i];
    if (light.props.intensity == 0.0)
      continue;

    // TODO: get the normals
  }

  // Spot lights
  for (int i = 0; i < MAX_LIGHTS; i++) {
    SpotLight light = spotLights[i];
    if (light.props.intensity == 0.0)
      continue;
  }

  color *= texture(textureSampler, texUV).rgb;
  color *= fragmentColor;
}
