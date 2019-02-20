#include "frustum.h"
#include "arrow.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
	double l = 4;
    double a = 0.3f;
    double b = 0;
    int n = 50;
    double arg = 0, arg1 = 0;
    
    GLfloat vertex_buffer_data[12 * 3 * n];

	for(int i=0; i<12 * 3 * n;)
	{
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = (l/2);

		vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = (l/2);

		arg += (2 * M_PI) / n;

		vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = (l/2);

        vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = - (l/2);

		vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = - (l/2);

		arg1 += (2 * M_PI) / n;

		vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = - (l/2);

        vertex_buffer_data[i++] = a * cos(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = a * sin(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = (l/2);

        vertex_buffer_data[i++] = b * cos(arg1 - (2*M_PI) / n);
		vertex_buffer_data[i++] = b * sin(arg1 - (2*M_PI) / n);
		vertex_buffer_data[i++] = - (l/2);

        vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = - (l/2);

        vertex_buffer_data[i++] = a * cos(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = a * sin(arg - (2*M_PI) / n);
		vertex_buffer_data[i++] = (l/2);

        vertex_buffer_data[i++] = a * cos(arg);
		vertex_buffer_data[i++] = a * sin(arg);
		vertex_buffer_data[i++] = (l/2);

        vertex_buffer_data[i++] = b * cos(arg1);
		vertex_buffer_data[i++] = b * sin(arg1);
		vertex_buffer_data[i++] = - (l/2);
	}
    this->object = create3DObject(GL_TRIANGLES, 12 * n, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Arrow::draw(glm::mat4 VP, float rotation) {
    this->body.rotation.y = rotation;
    glm::mat4 rota(1.0f);
    rota[2][0] = this->dir[0];
    rota[2][1] = this->dir[1];
    rota[2][2] = this->dir[2];
    rota[1][0] = -this->dir[1];
    rota[1][1] = this->dir[0];
    rota[1][2] = 0;
    glm::vec3 temp = glm::cross(this->dir, glm::vec3(-this->dir[1], this->dir[0], 0));
    rota[0][0] = temp[0];
    rota[0][1] = temp[1];
    rota[0][2] = temp[2];
    glm::mat4 translate = glm::translate (this->position);
    // VP = translate * rota * VP;
    // this->body.set_position(this->position.x, this->position.y, this->position.z);
    Matrices.model *= (translate * rota);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
}
