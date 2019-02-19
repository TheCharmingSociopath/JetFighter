#include "timer.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>

Timer::Timer(double interval) {
    prev = 0;
    this->interval = interval;
    this->seconds = 0;
    this->count = 0;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        ++count;
        if(count % 60 == 0)
        {
            ++seconds;
            count = 0;
        }
        return true;
    } else
        return false;
}
