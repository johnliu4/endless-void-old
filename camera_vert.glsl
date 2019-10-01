#version 330 core

layout(location = 0) in vec3 vert_modelspace_pos;
layout(location = 1) in vec3 surface_modelspace_norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 frag_modelspace_pos;
out vec3 out_vert_cameraspace_pos;
out vec3 out_surface_light_cameraspace_norm;
out vec3 out_surface_cameraspace_norm;

void main() {
	vec3 vert_worldspace_pos = (model * vec4(vert_modelspace_pos, 1.0)).xyz;
	vec3 vert_cameraspace_pos = (view * model * vec4(vert_modelspace_pos, 1.0)).xyz;
	out_surface_light_cameraspace_norm = normalize(vec3(-1.0, 3.0, -1.0));
	out_surface_cameraspace_norm = normalize(surface_modelspace_norm);
	gl_Position = proj * model * view * vec4(vert_modelspace_pos, 1.0);

	frag_modelspace_pos = vert_modelspace_pos;
}
