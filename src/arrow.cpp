#include "frustum.h"
#include "arrow.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->body = Frustum(x, y, z, COLOR_BLACK, 100, 0, 0.3f, 4);
    this->body.rotation = glm::vec3(0, 0, 0);
}

void Arrow::draw(glm::mat4 VP, float rotation) {
    this->body.rotation.y = rotation;
    this->body.set_position(this->position.x, this->position.y, this->position.z);
    this->body.draw(VP);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
}
