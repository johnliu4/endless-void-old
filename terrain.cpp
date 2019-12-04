#include "terrain.h"
//#include "loader.h"

#include <iostream>

Terrain::Terrain(const int width, const int height) {
	this->width = width;
	this->height = height;
	perlin_noise.generate(width + 1, height + 1);

	num_verts = width * height * 2 * 3;

	GLfloat* vertices = new GLfloat[(width + 1) * (height + 1) * 3];
	GLfloat* vertex_buffer_data = new GLfloat[num_verts * 3];
	GLfloat* norm_buffer_data = new GLfloat[num_verts * 3];
	
	GLfloat scale = 1.8f;


	GLfloat max = -1.0f;
	GLfloat min = 1.0f;

	// prepare vertex data with Perlin noise
	// this builds vertices going column by column, row by row
	for (int x = 0; x < width + 1; x++) {
		for (int z = 0; z < height + 1; z++) {
			vertices[(x * (height + 1) + z) * 3] = x * scale;
			vertices[(x * (height + 1) + z) * 3 + 1] = perlin_noise.get_value(x / 8.0f, z / 8.0f) * 1.3f;

			if (vertices[(x * (height + 1) + z) * 3 + 1] > max) {
				max = vertices[(x * (height + 1) + z) * 3 + 1];
			} else if (vertices[(x * (height + 1) + z) * 3 + 1] < min) {
				min = vertices[(x * (height + 1) + z) * 3 + 1];
			}

			vertices[(x * (height + 1) + z) * 3 + 2] = z * scale;
		}
	}

	// for each 'square' formed in the vertices, build two triangles
	// starting from the lower left corner of the square
	for (int x = 0; x < width; x++) {
		for (int z = 0; z < height; z++) {
			int starting_idx = x * (height + 1) + z + 1;
			glm::vec3 lower_left(
				vertices[starting_idx * 3],
				vertices[starting_idx * 3 + 1],
				vertices[starting_idx * 3 + 2]);
			glm::vec3 lower_right(
				vertices[(starting_idx + height + 1) * 3],
				vertices[(starting_idx + height + 1) * 3 + 1],
				vertices[(starting_idx + height + 1) * 3 + 2]);
			glm::vec3 upper_right(
				vertices[(starting_idx + height) * 3],
				vertices[(starting_idx + height) * 3 + 1],
				vertices[(starting_idx + height) * 3 + 2]);
			glm::vec3 upper_left(
				vertices[(starting_idx - 1) * 3],
				vertices[(starting_idx - 1) * 3 + 1],
				vertices[(starting_idx - 1) * 3 + 2]);

			glm::vec3 tri_norm1 = glm::normalize(glm::cross(upper_right - lower_left, upper_left - lower_left));
			glm::vec3 tri_norm2 = glm::normalize(glm::cross(lower_right - lower_left, upper_right - lower_left));
			norm_buffer_data[(x * height + z) * 18] = tri_norm1.x;
			norm_buffer_data[(x * height + z) * 18 + 1] = tri_norm1.y;
			norm_buffer_data[(x * height + z) * 18 + 2] = tri_norm1.z;
			vertex_buffer_data[(x * height + z) * 18] = lower_left.x;
			vertex_buffer_data[(x * height + z) * 18 + 1] = lower_left.y;
			vertex_buffer_data[(x * height + z) * 18 + 2] = lower_left.z;

			norm_buffer_data[(x * height + z) * 18 + 3] = tri_norm1.x;
			norm_buffer_data[(x * height + z) * 18 + 4] = tri_norm1.y;
			norm_buffer_data[(x * height + z) * 18 + 5] = tri_norm1.z;
			vertex_buffer_data[(x * height + z) * 18 + 3] = upper_right.x;
			vertex_buffer_data[(x * height + z) * 18 + 4] = upper_right.y;
			vertex_buffer_data[(x * height + z) * 18 + 5] = upper_right.z;

			norm_buffer_data[(x * height + z) * 18 + 6] = tri_norm1.x;
			norm_buffer_data[(x * height + z) * 18 + 7] = tri_norm1.y;
			norm_buffer_data[(x * height + z) * 18 + 8] = tri_norm1.z;
			vertex_buffer_data[(x * height + z) * 18 + 6] = upper_left.x;
			vertex_buffer_data[(x * height + z) * 18 + 7] = upper_left.y;
			vertex_buffer_data[(x * height + z) * 18 + 8] = upper_left.z;

			norm_buffer_data[(x * height + z) * 18 + 9] = tri_norm2.x;
			norm_buffer_data[(x * height + z) * 18 + 10] = tri_norm2.y;
			norm_buffer_data[(x * height + z) * 18 + 11] = tri_norm2.z;
			vertex_buffer_data[(x * height + z) * 18 + 9] = lower_left.x;
			vertex_buffer_data[(x * height + z) * 18 + 10] = lower_left.y;
			vertex_buffer_data[(x * height + z) * 18 + 11] = lower_left.z;

			norm_buffer_data[(x * height + z) * 18 + 12] = tri_norm2.x;
			norm_buffer_data[(x * height + z) * 18 + 13] = tri_norm2.y;
			norm_buffer_data[(x * height + z) * 18 + 14] = tri_norm2.z;
			vertex_buffer_data[(x * height + z) * 18 + 12] = lower_right.x;
			vertex_buffer_data[(x * height + z) * 18 + 13] = lower_right.y;
			vertex_buffer_data[(x * height + z) * 18 + 14] = lower_right.z;

			norm_buffer_data[(x * height + z) * 18 + 15] = tri_norm2.x;
			norm_buffer_data[(x * height + z) * 18 + 16] = tri_norm2.y;
			norm_buffer_data[(x * height + z) * 18 + 17] = tri_norm2.z;
			vertex_buffer_data[(x * height + z) * 18 + 15] = upper_right.x;
			vertex_buffer_data[(x * height + z) * 18 + 16] = upper_right.y;
			vertex_buffer_data[(x * height + z) * 18 + 17] = upper_right.z;
		}
	}

	//for (int i = 0; i < num_norms; i++) {
	//	std::cout << norm_buffer_data[i * 3] << ", " << norm_buffer_data[i * 3 + 1] << ", " << norm_buffer_data[i * 3 + 2] << std::endl;
	//}

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, num_verts * 3 * sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &norm_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, norm_buffer);
	glBufferData(GL_ARRAY_BUFFER, num_verts * 3 * sizeof(GLfloat), norm_buffer_data, GL_STATIC_DRAW);

	// free data once it has been binded and copied into buffer
	delete[] vertices;
	delete[] vertex_buffer_data;
	delete[] norm_buffer_data;

}

Terrain::~Terrain() {}

void Terrain::render() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(
		0, // attribute 0, must match layout in shader
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized
		0, // stride
		(void*) 0 // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, norm_buffer);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*) 0
	);

	glDrawArrays(GL_TRIANGLES, 0, num_verts * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}