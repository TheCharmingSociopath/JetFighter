#include "ring.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Ring::Ring(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float arg = 0, n = 40;
    int coordinates = 18 * 3 * n;
	GLfloat vertex_buffer_data[coordinates];

    this->box.len_x = 2 * this->radius;
    this->box.len_y = 2 * this->radius;
    this->box.len_z = 0.5f;
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;

    for (int i=0; i<coordinates;)
    {
        vertex_buffer_data[i++] = this->radius * cos(arg);
		vertex_buffer_data[i++] = this->radius * sin(arg);
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = this->radius * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = this->radius * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = this->radius * cos(arg);
		vertex_buffer_data[i++] = this->radius * sin(arg);
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg);
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg);
		vertex_buffer_data[i++] = 0.0f;

        
        vertex_buffer_data[i++] = this->radius * cos(arg);
		vertex_buffer_data[i++] = this->radius * sin(arg);
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = this->radius * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = this->radius * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = this->radius * cos(arg);
		vertex_buffer_data[i++] = this->radius * sin(arg);
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg);
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg);
		vertex_buffer_data[i++] = 0.5f;


        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg);
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg);
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg);
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg);
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.5f;
    

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.5f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg);
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg);
		vertex_buffer_data[i++] = 0.0f;

        vertex_buffer_data[i++] = (this->radius + 0.5f) * cos(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = (this->radius + 0.5f) * sin(arg + (2 * M_PI / n));
		vertex_buffer_data[i++] = 0.0f;

        arg += 2 * M_PI / n;
    }
    this->object = create3DObject(GL_TRIANGLES, coordinates / 3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick() {
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;
}
