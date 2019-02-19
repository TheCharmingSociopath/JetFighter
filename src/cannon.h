#include "main.h"
#include "sphere.h"

#ifndef CANNON_H
#define CANNON_H
#define GLM_ENABLE_EXPERIMENTAL


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, float t, float p);
    glm::vec3 position;
    Sphere sphere;
    float rotation, speed_y, theta, phi;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // CANNON_H
