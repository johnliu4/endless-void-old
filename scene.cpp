#include <glm/gtc/matrix_transform.hpp>

#include "scene.h"
#include "render_loader.h"

Scene::Scene() {
	default_program_id = glCreateProgram();
	GLuint vertex_id = load_shader("default_vert.glsl", GL_VERTEX_SHADER);
	GLuint fragment_id = load_shader("default_frag.glsl", GL_FRAGMENT_SHADER);
	glAttachShader(default_program_id, vertex_id);
	glAttachShader(default_program_id, fragment_id);
	glLinkProgram(default_program_id);
	glDetachShader(default_program_id, vertex_id);
	glDetachShader(default_program_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	camera_fov = glm::radians(60.0f);
	camera_aspect_ratio = 16.0f / 9.0f;
	camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	camera_dir = glm::vec3(1.0f, 0.0f, 0.0f);
	proj_matrix = glm::perspective(camera_fov, camera_aspect_ratio, 0.1f, 100.0f);

	model_matrix_id = glGetUniformLocation(default_program_id, "model");
	view_matrix_id = glGetUniformLocation(default_program_id, "view");
	proj_matrix_id = glGetUniformLocation(default_program_id, "proj");
	texture_sampler_id = glGetUniformLocation(default_program_id, "texture_sampler");

	glClearColor(0.521568627, 0.807843137, 0.921568627, 1.0f);

	glUniform1i(texture_sampler_id, 0);
}

Scene::~Scene() {
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(default_program_id);

	view_matrix = glm::lookAt(camera_pos, camera_pos + camera_dir, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view_matrix[0][0]);
	glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, &proj_matrix[0][0]);

	for (auto it = entity_list.begin(); it != entity_list.end(); it++) {
		(*it)->render(model_matrix_id);
	}
}

void Scene::add_entity(SceneEntity* entity) {
	entity_list.push_back(entity);
}

void Scene::remove_entity(SceneEntity* entity) {
	entity_list.remove(entity);
}

void Scene::set_camera_pos(glm::vec3 pos) {
	camera_pos = pos;
}

void Scene::set_camera_dir(glm::vec3 dir) {
	camera_dir = dir;
}
