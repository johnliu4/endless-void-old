#version 330 core

in vec3 world_pos;
in vec3 camera_norm;

out vec3 color;

uniform vec3 world_light_pos;

void main() {
	vec3 light_color = vec3(1, 1, 1);
	float light_power = 50.0f;

	vec3 mat_diffuse_color = vec3(world_pos.y / 5.0f, 0.8f, 0.9f);
	float dist = length(world_light_pos - world_pos);

	vec3 n = normalize(camera_norm);
	vec3 l = normalize(camera_light_dir);
	float cos_theta = clamp(dot(camera_norm, l), 0, 1);

	color = mat_diffuse * light_color * light_power * cos_theta / (dist * dist);
}