#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "ball.h"

using namespace std;

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE: quit(window);
                                  break;

            default: break;
        }
    }
}

void keyboardChar(GLFWwindow *window, unsigned int key) {

    if(key == 'Q' || key == 'q')
    {
        quit(window);
    }

    else if(key == 'd')
    {
        move_right();
    }

    else if(key == 'a')
    {
        move_left();
    }

    else if(key == ' ')
    {
        move_up();
    }
}

void mouseButton(GLFWwindow *window, int button, int action, int mods) {

    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            return;
        }
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{

}
