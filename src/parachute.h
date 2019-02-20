#include "main.h"
#include "sphere.h"
#include "frustum.h"
#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float z);
    glm::vec3 position;
    float radius = 6, y = 120, rotation = -90;
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object[2];
};

#endif // PARACHUTE_H
