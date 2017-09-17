#version 330 core

layout(location = 0) in vec3 vertexPosition_ms;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec3 fragmentColor;
out vec2 texUV;

uniform mat4 mvp;

void main() {
  fragmentColor = vertexColor;
  texUV = vertexUV;

  gl_Position = mvp * vec4(vertexPosition_ms, 1.0);
}
