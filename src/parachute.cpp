#include "parachute.h"
#include "frustum.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

const float PARACHUTE_GRAVITY = 0.1;

Parachute::Parachute(float x, float z) {
    this->position = glm::vec3(x, this->y, z);

    int n = 100, idx = 0;
    int coordinates = 9 * n * n / 2;
	GLfloat vertex_buffer_data[coordinates];
    float theta = M_PI / 2, phi = 0.0f, arg = (2 * M_PI) / n;

    for (int i=0; i<n/4; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            vertex_buffer_data[idx++] = this->radius * sin(theta) * cos(phi);
            vertex_buffer_data[idx++] = this->radius * sin(theta) * sin(phi);
            vertex_buffer_data[idx++] = this->radius * cos(theta);

            vertex_buffer_data[idx++] = this->radius * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = this->radius * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = this->radius * cos(theta);

            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = this->radius * cos(theta - arg);

            vertex_buffer_data[idx++] = this->radius * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = this->radius * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = this->radius * cos(theta);

            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = this->radius * cos(theta - arg);

            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * cos(phi + arg);
            vertex_buffer_data[idx++] = this->radius * sin(theta - arg) * sin(phi + arg);
            vertex_buffer_data[idx++] = this->radius * cos(theta - arg);

            phi += arg;
        }
        theta -= arg;
    }
    this->object[0] = create3DObject(GL_TRIANGLES, coordinates / 3, vertex_buffer_data, COLOR_PARACHUTE, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->position.y -= PARACHUTE_GRAVITY;
}
