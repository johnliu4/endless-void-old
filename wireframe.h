#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "scene_entity.h"

/* A wireframe renderer. */

class Wireframe : public SceneEntity {
public:
	Wireframe(GLuint vertex_buffer_id, unsigned int num_vertices);
	void render(GLuint model_matrix_id);
};


#endif WIREFRAME_H