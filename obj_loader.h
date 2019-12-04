#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <string>
#include <vector>
#include <glew/glew.h>

#include "scene_entity.h"

/* A simple loader for Wavefront .obj files. */
struct WavefrontObject {
	std::string name;
	GLuint vertex_buffer_id;
	GLuint uv_buffer_id;
	std::vector<SceneEntityTexture> texture_list;
};

class WavefrontObjectManager {
private:	
	static WavefrontObjectManager* singleton;
	std::vector<WavefrontObject> obj_list;
	
	~WavefrontObjectManager();
public:
	static WavefrontObjectManager* get_instance();
	void add_object(std::string name,
		GLuint vertex_buffer_id, GLuint uv_buffer_id, std::vector<SceneEntityTexture> texture_list);
	const WavefrontObject* get_object(std::string name);
};

/* Splits a string up by a given delimiter. */
std::vector<std::string> split(std::string str, char delimiter);

/**
 * Loads an .obj file into a SceneEntity object.
 * A very simple implementation is used here.
 * usemtl should indicate the page of the image to be used.
 * mtl files and mtllib are not used.
 * Only triangular faces are supported.
 */
SceneEntity* load_obj(const char* file_path);

#endif