#include "texture_manager.h"
#include "render_loader.h"

TextureManager::~TextureManager() {
	for (std::list<TextureIdentifier>::iterator it = texture_list.begin(); it != texture_list.end(); it++) {
		glDeleteTextures(1, &(it->texture_id));
	}

	texture_list.clear();
}

bool TextureManager::exists(std::string file_name) const {
	for (std::list<TextureIdentifier>::const_iterator it = texture_list.begin(); it != texture_list.end(); it++) {
		if (it->file_name == file_name) {
			return true;
		}
	}

	return false;
}

void TextureManager::add_texture(std::string file_name) {
	if (!this->exists(file_name)) {
		GLuint texture_id = load_png(file_name.c_str());
		texture_list.push_back({ file_name, texture_id });
	}
}

GLuint TextureManager::get_texture(std::string file_name) {
	for (std::list<TextureIdentifier>::iterator it = texture_list.begin(); it != texture_list.end(); it++) {
		if (it->file_name == file_name) {
			return it->texture_id;
		}
	}

	GLuint texture_id = load_png(("./resources/" + file_name).c_str());
	texture_list.push_back({ file_name, texture_id });
	return texture_id;
}