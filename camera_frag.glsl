#version 330 core

in vec3 vert_modelspace_pos;
in vec3 out_surface_light_cameraspace_norm;
in vec3 out_surface_cameraspace_norm;

out vec3 out_color;

void main() {
	vec3 surface_color = vec3(0.486, vert_modelspace_pos.y / 50.0f, vert_modelspace_pos.y / 50.0f);

	float cos_theta = clamp(dot(out_surface_cameraspace_norm, out_surface_light_cameraspace_norm), 0.4, 1.0);
	float light_intensity = 1.0;

	out_color = surface_color * light_intensity * cos_theta;
}