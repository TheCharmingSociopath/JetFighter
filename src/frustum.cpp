#include "frustum.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Frustum::Frustum(float x, float y, float z, color_t color, int n, float a, float b, float l) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
	this->length = l;
    double arg = 0, arg1 = 0;
    
    GLfloat vertex_buffer_data[12 * 3 * n];

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
    this->object[0] = create3DObject(GL_TRIANGLES, 12 * n, vertex_buffer_data, color, GL_LINE);
}

void Frustum::draw(glm::mat4 VP, float rot_x, float rot_y, float rot_z) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(rot_x, rot_y, rot_z));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
}

void Frustum::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Frustum::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
