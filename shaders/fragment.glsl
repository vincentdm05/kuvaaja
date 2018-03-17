#version 330 core

in vec3 fragmentNormal; // In world space
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

// TODO: use UBOs instead
uniform PointLight pointLights[MAX_LIGHTS];
// uniform DirectionalLight directionalLights[MAX_LIGHTS];
uniform vec4 directionalLights;
uniform SpotLight spotLights[MAX_LIGHTS];

uniform sampler2D textureSampler;

void main() {
  vec3 normal = normalize(fragmentNormal);

  // Ambient light
  color = ambientLight.xyz * ambientLight.w;

  // Point lights
  for (int i = 0; i < MAX_LIGHTS; i++) {
    PointLight light = pointLights[i];
    if (light.props.intensity == 0.0)
      continue;
  }

  // Directional lights
  // for (int i = 0; i < MAX_LIGHTS; i++) {
  //   DirectionalLight light = directionalLights[i];
  //   if (light.props.intensity == 0.0)
  //     continue;

    // float cosTheta = clamp(dot(light.direction.xyz, normal), 0.0, 1.0);
    // color += light.props.intensity * light.props.color * cosTheta;
  // }
  color += clamp(dot(directionalLights.xyz, normal), 0.0, 1.0);

  // Spot lights
  for (int i = 0; i < MAX_LIGHTS; i++) {
    SpotLight light = spotLights[i];
    if (light.props.intensity == 0.0)
      continue;
  }

  // TODO: use permutation
  vec3 texture = texture(textureSampler, texUV).rgb;
  if (texture != vec3(0))
    color *= texture;

  color *= fragmentColor;
}
