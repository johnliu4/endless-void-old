#version 330 core

layout(location = 0) in vec3 vert_pos_modelspace;
layout(location = 1) in vec2 vert_uv;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(vert_pos_modelspace, 1);
	uv = vert_uv;
}