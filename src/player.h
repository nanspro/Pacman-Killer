#include "main.h"

#ifndef Player_H
#define Player_H


class Player {
public:
    Player() {}
    Player(float x, float y, float r, color_t color);
    glm::vec3 position;
    float radius;
    float rotation;
    int score;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int in_pond);
    void right(int in_pond);
    void left(int in_pond);
    void jump(int on_tramp);
    double speedx;
    double speedy;
    double gravity;
    double gravityspeed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Player_H
