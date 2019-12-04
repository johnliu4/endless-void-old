#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "wireframe.h"

Wireframe::Wireframe(GLuint vertex_buffer_id, unsigned int num_vertices)
	: SceneEntity(vertex_buffer_id, num_vertices) {
}


void Wireframe::render(GLuint model_matrix_id) {
	glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), pos), scale);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_LINES, 0, num_vertices);
	glDisableVertexAttribArray(0);
}