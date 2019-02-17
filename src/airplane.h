#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, float z, color_t color, int n, float a, float b, float l);
    glm::vec3 position, rotation;
    float length;
    void draw(glm::mat4 VP, float rot_x, float rot_y, float rot_z);
    void set_position(float x, float y, float z);
    void set_rotation(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object[3];
};

#endif // AIRPLANE_H
