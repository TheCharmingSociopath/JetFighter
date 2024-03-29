#include "main.h"

#ifndef FRUSTUM_H
#define FRUSTUM_H


class Frustum {
public:
    Frustum() {}
    Frustum(float x, float y, float z, color_t color, int n, float a, float b, float l);
    glm::vec3 position, rotation;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_rotation(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object[3];
};

#endif // FRUSTUM_H
