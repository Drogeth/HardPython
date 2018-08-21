#version 400
in vec2 UV;
in vec3 Color;

out vec4 fragment_color;

uniform sampler2D tileset;

void main() {
    fragment_color = texture(tileset, UV) * vec4(Color, 1.0);
}