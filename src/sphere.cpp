#include "sphere.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Sphere::Sphere(float x, float y, float z, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = r;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 100, idx = 0;
    int coordinates = 9 * n * n;
	GLfloat vertex_buffer_data[coordinates];
    float theta = M_PI / 2, phi = 0.0f, arg = (2 * M_PI) / n;

    for (int i=0; i<n/4; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi);
            vertex_buffer_data[idx++] = r * cos(theta);

            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = r * cos(theta);

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = r * cos(theta - arg);

            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = r * cos(theta);

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = r * cos(theta - arg);

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi + arg);
            vertex_buffer_data[idx++] = r * cos(theta - arg);



            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi);
            vertex_buffer_data[idx++] = - (r * cos(theta));

            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = - (r * cos(theta));

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = - (r * cos(theta - arg));

            vertex_buffer_data[idx++] = r * sin(theta) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta) * sin(phi + arg);
            vertex_buffer_data[idx++] = - (r * cos(theta));

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi);
            vertex_buffer_data[idx++] = - (r * cos(theta - arg));

            vertex_buffer_data[idx++] = r * sin(theta - arg) * cos(phi + arg);
            vertex_buffer_data[idx++] = r * sin(theta - arg) * sin(phi + arg);
            vertex_buffer_data[idx++] = - (r * cos(theta - arg));
            phi += arg;
        }
        theta -= arg;
    }
    this->object = create3DObject(GL_TRIANGLES, coordinates / 3, vertex_buffer_data, color, GL_LINE);
}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sphere::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sphere::tick() {
}
