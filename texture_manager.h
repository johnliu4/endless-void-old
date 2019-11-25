#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <list>
#include <string>
#include <glew/glew.h>

/**
 * A unique identifier for textures.
 * The file_path is the name of the resources in the assets folder;
 * this field should be unique across all textures.
 */
struct TextureIdentifier {
	std::string file_name;
	GLuint texture_id;
};

/**
 * A managing system for textures to ensure that no texture is ever
 * loaded more than once and to manage textures in memory.
 */
class TextureManager {
private:
	std::list<TextureIdentifier> texture_list;

public:
	// frees up textures in memory
	~TextureManager();

	// returns whether or not a texture has been loaded already
	bool exists(std::string file_name) const;

	// adds a texture if it does not already exist
	void add_texture(std::string file_name);

	// gets the id of a given texture
	// if the texture does not already exist, it will be created
	GLuint get_texture(std::string file_name);
};

#endif