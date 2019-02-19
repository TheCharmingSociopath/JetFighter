#include "cannon.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

double Cannon_gravity = 0.5, tim = (double) 1/60;

Cannon::Cannon(float x, float y, float z, float t, float p) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->theta = t;
    this->phi = p;
    this->sphere = Sphere (x, y, z, 2, COLOR_BLACK);
}

void Cannon::draw(glm::mat4 VP) {
    this->sphere.position.x = this->position.x;
    this->sphere.position.y = this->position.y;
    this->sphere.position.z = this->position.z;
    this->sphere.draw(VP);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    
}
