#version 400
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aColor;

out vec2 UV;
out vec3 Color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    UV = aUV;
    Color = aColor;
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}