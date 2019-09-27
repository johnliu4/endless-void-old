#ifndef CAMERA_H
#define CAMERA_H

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::mat4 proj_mat;
	glm::mat4 view_mat;
	glm::mat4 model_mat;
	glm::vec3 pos;
	GLfloat speed;
	GLfloat yaw;
	GLfloat pitch;
	GLuint shader_mat_id;
	GLuint program_id;
public:
	Camera();
	~Camera();
	void update();
	void render();
};

#endif