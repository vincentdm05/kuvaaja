#version 330 core

layout(location = 0) in vec3 vertexPosition_ms;

void main() {
  gl_Position.xyz = vertexPosition_ms;
  gl_Position.w = 1.0;
}
