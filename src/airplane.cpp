#include "airplane.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Airplane::Airplane(float x, float y, float z, color_t color, int n, float a, float b, float l) {
    this->position = glm::vec3(x, y, z);
    this->rotation = glm::vec3(0, 0, 0);
	this->length = l;
    // speed = 1;
    double arg = 0, arg1 = 0;
    
    GLfloat vertex_buffer_data[12 * 3 * n];

	this->box.len_x = (a + b) / 2;
    this->box.len_y = (a + b) / 2;
    this->box.len_z = l;
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;

	for(int i=0; i<12 * 3 * n;)
	{
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = z + (l/2);

		vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = z + (l/2);

		arg += (2 * M_PI) / n;

		vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = z + (l/2);

        vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = z - (l/2);

		vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = z - (l/2);

		arg1 += (2 * M_PI) / n;

		vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = z - (l/2);

        vertex_buffer_data[i++] = a * cos(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = a * sin(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = z + (l/2);

        vertex_buffer_data[i++] = b * cos(arg1 - (2*M_PI) / n);
		vertex_buffer_data[i++] = b * sin(arg1 - (2*M_PI) / n);
		vertex_buffer_data[i++] = z - (l/2);

        vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = z - (l/2);

        vertex_buffer_data[i++] = a * cos(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = a * sin(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = z + (l/2);

        vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = z + (l/2);

        vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = z - (l/2);
	}
    this->object[0] = create3DObject(GL_TRIANGLES, 12 * n, vertex_buffer_data, color, GL_FILL);
}

void Airplane::draw(glm::mat4 VP, float rot_x, float rot_y, float rot_z) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 pitch    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0)); // X = Pitch
    glm::mat4 yaw    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0)); // Y = Yaw
    glm::mat4 roll    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1)); // Z = Roll
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * yaw * pitch * roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
}

void Airplane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Airplane::set_rotation(float x, float y, float z) {
    this->rotation = glm::vec3(x, y, z);
}

void Airplane::tick() {
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;
}
