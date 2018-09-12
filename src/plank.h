#include "main.h"

#ifndef Plank_H
#define Plank_H


class Plank {
public:
    Plank() {}
    Plank(float x, float y, float length, float width, color_t color);
    glm::vec3 position;
    //float radius;
    float length;
    float width;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Plank_H
