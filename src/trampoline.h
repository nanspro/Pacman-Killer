#include "main.h"

#ifndef Trampoline_H
#define Trampoline_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color);
    glm::vec3 position;
    //float radius;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    //void tick();
    //double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Trampoline_H
