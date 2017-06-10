#version 330 core
in vec3 fcolor; ///< passed by vshader
out vec3 color; ///< output color
in vec3 uv;
uniform vec2 resolution;
uniform sampler2D backbuffer;


void main() {
    color = fcolor;
}
