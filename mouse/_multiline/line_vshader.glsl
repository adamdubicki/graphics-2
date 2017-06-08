#version 330 core

in vec3 position;
uniform mat4 projection;
uniform mat4 model_view;

void main() {
    gl_Position = vec4(position, 1.0);
}

