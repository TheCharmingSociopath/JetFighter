#include "main.h"
#include "frustum.h"
#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    Frustum body;
    void draw(glm::mat4 VP, float rotation);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object[2];
};

#endif // ARROW_H
