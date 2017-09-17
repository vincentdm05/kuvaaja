#version 330 core

in vec3 fragmentColor;
in vec2 texUV;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
  color = texture(textureSampler, texUV).rgb;
  color *= fragmentColor;
}
