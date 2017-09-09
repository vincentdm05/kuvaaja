#version 330 core

layout(location = 0) in vec3 vertexPosition_ms;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(vertexPosition_ms, 1.0);
}
