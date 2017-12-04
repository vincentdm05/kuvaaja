#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;
layout(location = 3) in vec2 vertexUV;

out vec3 fragmentNormal;
out vec3 fragmentColor;
out vec2 texUV;

uniform mat4 modelViewProjection;
uniform mat4 inverseTransposeModel;

void main() {
  // TODO: get correct transform for normals
  fragmentNormal = (inverseTransposeModel * vec4(vertexNormal, 0.0)).xyz;
  fragmentColor = vertexColor;
  texUV = vertexUV;

  gl_Position = modelViewProjection * vec4(vertexPosition, 1.0);
}
