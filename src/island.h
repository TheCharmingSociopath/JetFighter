#include "main.h"
#include "sphere.h"
#include "frustum.h"
#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float z, color_t color);
    glm::vec3 position;
    float radius = 50, y = -40, rotation;
    bounding_box_t box;
    int activation_time = 0;
    Sphere sphere;
    bool active = false;
    Frustum stand, gun;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object[2];
};

#endif // ISLAND_H
