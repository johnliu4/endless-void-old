#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

#include "render_engine.h"
#include "obj_loader.h"

WavefrontObjectManager* WavefrontObjectManager::singleton = nullptr;

WavefrontObjectManager::~WavefrontObjectManager() {
	obj_list.clear();
	obj_list.shrink_to_fit();
}

WavefrontObjectManager* WavefrontObjectManager::get_instance() {
	if (WavefrontObjectManager::singleton == nullptr) {
		WavefrontObjectManager::singleton = new WavefrontObjectManager();
	}

	return WavefrontObjectManager::singleton;
}

const WavefrontObject* WavefrontObjectManager::get_object(std::string name) {
	for (std::vector<WavefrontObject>::iterator it = obj_list.begin();
		it != obj_list.end(); it++) {
		if (it->name == name) {
			return &(*it);
		}
	}

	return nullptr;
}

void WavefrontObjectManager::add_object(std::string name,
	GLuint vertex_buffer_id, GLuint uv_buffer_id, std::vector<SceneEntityTexture> texture_list) {
	// check if the object already exists
	for (std::vector<WavefrontObject>::iterator it = obj_list.begin();
		it != obj_list.end(); it++) {
		if (it->name == name) {
			return;
		}
	}

	WavefrontObject obj;
	obj.name = name;
	obj.vertex_buffer_id = vertex_buffer_id;
	obj.uv_buffer_id = uv_buffer_id;
	obj.texture_list = texture_list;
	obj_list.push_back(obj);
}

SceneEntity* load_obj(const char* file_path) {
	WavefrontObjectManager* obj_manager = WavefrontObjectManager::get_instance();
	// check if the object has already been loaded before
	const WavefrontObject* existing_obj = obj_manager->get_object(file_path);
	if (existing_obj != nullptr) {
		return new SceneEntity(existing_obj->vertex_buffer_id, existing_obj->uv_buffer_id, existing_obj->texture_list);
	}

	TextureManager* texture_manager = RenderEngine::get_instance()->get_texture_manager();

	std::ifstream obj_file;
	obj_file.open(file_path, std::ios::in);

	if (obj_file.is_open()) {
		std::string line;

		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvs;
		std::vector<GLfloat> normals;

		std::vector<GLfloat> vertex_buffer;
		std::vector<GLfloat> uv_buffer;

		// keep track of the current texture being used and the number of vertices
		// that the texture is applied to
		bool using_textures = false;
		GLuint current_texture = 0;
		GLuint total_num_vertices = 0;
		GLuint current_num_vertices = 0;
		std::vector<SceneEntityTexture> texture_list;


		while (getline(obj_file, line)) {
			// ignore blank lines and comments
			if (line.length() == 0 || line[0] == '#') {
				continue;
			}

			std::vector<std::string> tokens = split(line, ' ');
			if (tokens[0] == "v") {
				vertices.push_back(std::stof(tokens[1]));
				vertices.push_back(std::stof(tokens[2]));
				vertices.push_back(std::stof(tokens[3]));
			} else if (tokens[0] == "vt") {
				uvs.push_back(std::stof(tokens[1]));
				uvs.push_back(std::stof(tokens[2]));
			} else if (tokens[0] == "vn") {
				normals.push_back(std::stof(tokens[1]));
				normals.push_back(std::stof(tokens[2]));
				normals.push_back(std::stof(tokens[3]));
			} else if (tokens[0] == "usemtl") {
				// usemtl will indicate the name of the image used for this loader
				std::string texture_name = tokens[1];
				if (!using_textures) {
					using_textures = true;
				} else {
					// add the previous texture to the list
					SceneEntityTexture texture;
					texture.texture_id = current_texture;
					texture.start_index = total_num_vertices;
					texture.num_vertices = current_num_vertices;
					total_num_vertices += current_num_vertices;
					texture_list.push_back(texture);
				}

				current_texture = texture_manager->get_texture(texture_name);
				current_num_vertices = 0;
			} else if (tokens[0] == "f") {
				current_num_vertices += 3;

				std::vector<std::string> v1 = split(tokens[1], '/');
				std::vector<std::string> v2 = split(tokens[2], '/');
				std::vector<std::string> v3 = split(tokens[3], '/');

				// get vertex position data
				int index1 = std::stoi(v1[0]) - 1;
				int index2 = std::stoi(v2[0]) - 1;
				int index3 = std::stoi(v3[0]) - 1;
				vertex_buffer.push_back(vertices[index1 * 3]);
				vertex_buffer.push_back(vertices[index1 * 3 + 1]);
				vertex_buffer.push_back(vertices[index1 * 3 + 2]);
				vertex_buffer.push_back(vertices[index2 * 3]);
				vertex_buffer.push_back(vertices[index2 * 3 + 1]);
				vertex_buffer.push_back(vertices[index2 * 3 + 2]);
				vertex_buffer.push_back(vertices[index3 * 3]);
				vertex_buffer.push_back(vertices[index3 * 3 + 1]);
				vertex_buffer.push_back(vertices[index3 * 3 + 2]);

				// get uv data
				index1 = std::stoi(v1[1]) - 1;
				index2 = std::stoi(v2[1]) - 1;
				index3 = std::stoi(v3[1]) - 1;
				uv_buffer.push_back(uvs[index1 * 2]);
				uv_buffer.push_back(uvs[index1 * 2 + 1]);
				uv_buffer.push_back(uvs[index2 * 2]);
				uv_buffer.push_back(uvs[index2 * 2 + 1]);
				uv_buffer.push_back(uvs[index3 * 2]);
				uv_buffer.push_back(uvs[index3 * 2 + 1]);
			}
		}

		// add the final texture
		SceneEntityTexture texture;
		texture.texture_id = current_texture;
		texture.start_index = total_num_vertices;
		texture.num_vertices = current_num_vertices;
		total_num_vertices += current_num_vertices;
		texture_list.push_back(texture);

		GLuint vertex_buffer_id;
		GLuint uv_buffer_id;

		glGenBuffers(1, &vertex_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer.size(), &vertex_buffer[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uv_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uv_buffer.size(), &uv_buffer[0], GL_STATIC_DRAW);

		obj_manager->add_object(file_path, vertex_buffer_id, uv_buffer_id, texture_list);
		SceneEntity* entity = new SceneEntity(vertex_buffer_id, uv_buffer_id, texture_list);
		obj_file.close();
		return entity;
	} else {
		std::cout << "Load OBJ error " << file_path << std::endl;
	}
}

std::vector<std::string> split(std::string str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}
