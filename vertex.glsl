#version 330 core

layout(location = 0) in vec3 vertex_worldspace;
layout(location = 1) in vec3 normal_worldspace;

out vec3 
out vec3 camera_norm;
out vec3 norm;

uniform vec3 = world_light_pos;

void main() {
	gl_Position.xyz = vertex_pos_modelspace;
	gl_Position.w = 1.0;

	norm = normal_worldspace;
}