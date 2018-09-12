#include "pond.h"
#include "main.h"

Pond::Pond(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius = r;
    this->rotation = 0;
    int pos = 0,i,j,n = 100;
        GLfloat g_vertex_buffer_data[9*n];
        float pi = 3.14, angle = pi, theta=(2*pi)/(2*n);
        for(i = 0; i < n ; i++){
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            for(j = 0; j < 2 ; j++){
                g_vertex_buffer_data[pos++]= cos(angle)*this->radius;
                g_vertex_buffer_data[pos++]= sin(angle)*this->radius;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += theta;
            }
            angle-=theta;
        }
    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 16, 2 };
    return bbox;
}
