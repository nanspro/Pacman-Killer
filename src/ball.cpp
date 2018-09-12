#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius = r;
    this->rotation = 0;
    nplank= -1;
    angle = -1;
    speed = 0.005;
    int pos = 0,i,j,n = 100;
        GLfloat g_vertex_buffer_data[9*n];
        float pi = 3.14, angle = 0, theta=(2*pi)/n;
        i = 0;
        while(i < n)
        {
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            for(j=0;j<2;j++){
                g_vertex_buffer_data[pos++]= cos(angle)*this->radius;
                g_vertex_buffer_data[pos++]= sin(angle)*this->radius;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += theta;
            }
            angle-=theta;
            ++i;
        }

    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= speed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float w = this->radius, h = this->radius;
    bounding_box_t bbox = { x, y, 2*w, 2*h };
    return bbox;
}
