#include "main.h"
#include "frustum.h"
#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z);
    glm::vec3 position, dir;
    float rotation;
    Frustum body;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // MISSILE_H
