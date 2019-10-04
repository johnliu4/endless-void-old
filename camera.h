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
	// yaw rotation in radians
	// positive going CCW when viewing from positive y-axis
	// range: 0 to pi, where 0 is facing local x-axis
	GLfloat yaw;
	// pitch rotation in radians
	// positive going CCW when going from camera's local z-axis
	// range -pi/2 to pi/2 where 0 is facing local x-axis
	GLfloat pitch;

	GLuint shader_model_id;
	GLuint shader_view_id;
	GLuint shader_proj_id;
	GLuint shader_light_pos_id;
	GLuint program_id;
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 dir);
	~Camera();
	void use_program();

	void set_yaw(GLfloat yaw);
	GLfloat get_yaw();
	void set_pitch(GLfloat pitch);
	GLfloat get_pitch();
	void set_pos(glm::vec3 pos);
	glm::vec3 get_pos();
};

#endif