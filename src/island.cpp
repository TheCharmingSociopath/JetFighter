#include "island.h"
#include "sphere.h"
#include "frustum.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL

Island::Island(float x, float z, color_t color) {
    this->position = glm::vec3(x, this->y, z);
    this->sphere = Sphere (x, this->y, z, this->radius, color);
    this->stand = Frustum (x, 1, z, COLOR_STAND, 4, 2, 2, 2);
    this->gun = Frustum (x, 3, z, COLOR_GUN, 100, 0.5f, 0.5f, 1.5f);
}

void Island::draw(glm::mat4 VP) {
    this->sphere.draw(VP);
    this->stand.draw(VP);
    this->gun.draw(VP);
}

void Island::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Island::tick() {
}
