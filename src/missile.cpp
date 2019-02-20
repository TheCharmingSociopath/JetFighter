#include "frustum.h"
#include "missile.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Missile::Missile(float x, float y, float z) {
    this->box.len_x = 2;
    this->box.len_y = 2;
    this->box.len_z = 2;

    this->position = glm::vec3(x, y, z);
    this->body = Frustum(x, y, z, COLOR_MISSILE, 100, 0.5f, 0.5f, 2);
    this->body.rotation = glm::vec3(0, 0, 0);
}

void Missile::draw(glm::mat4 VP) {
    this->body.set_position(this->position.x, this->position.y, this->position.z);
    this->body.draw(VP);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    this->position.y -= 0.8f;
    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;
}
