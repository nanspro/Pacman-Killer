#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int pos = 0,i,j,n = 100;
        GLfloat g_vertex_buffer_data[9*n];
        GLfloat l_vertex_buffer_data[9*n + 36];
        float pi = 3.14, angle = pi, theta = (2 * pi) / (2 * n);
        for(i = 0; i < n ; i++)
        {
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            g_vertex_buffer_data[pos++]= 0.0f;
            for(j = 0; j < 2 ; j++)
            {
                g_vertex_buffer_data[pos++]= cos(angle)*1;
                g_vertex_buffer_data[pos++]= sin(angle)*1;
                g_vertex_buffer_data[pos++]= 0.0f;
                angle += theta;
            }
            angle-=theta;
        }
        static const GLfloat vertex_buffer_data[] = {
            -1, 0, 0,
            -1.3,  0, 0,
            -1,  -1.3, 0,

            -1,  -1.3, 0,
            -1.3, -1.3, 0,
            -1.3, 0, 0,

             1, 0, 0,
            1.3,  0, 0,
            1.3,  -1.3, 0,

            1.3,  -1.3, 0,
            1, -1.3, 0,
            1, 0, 0

        };

        for(i = 0; i <9*n + 36; i++)
        {
            if(i < 9*n)
                l_vertex_buffer_data[i] = g_vertex_buffer_data[i];
            else
                l_vertex_buffer_data[i] = vertex_buffer_data[i-9*n];
        }

    this->object = create3DObject(GL_TRIANGLES, 3*n+12, l_vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 16, 2 };
    return bbox;
}
