#include "main.h"
#include "stdlib.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "pond.h"
#include "plank.h"
#include "ground.h"
#include "math.h"
#include "trampoline.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Player player;
Pond pond;
Ground ground[5];
Trampoline tramp;
Plank plank[100];
Ball ball[100];

float screen_zoom = 1,pi = 3.14, s_c_x = 0, s_c_y = 0, r, x, y, angle, pl_x, pl_y, pl_l, pl_w, sq_y, p_x, p_y;

color_t color[] = {COLOR_BALL1, COLOR_BALL2, COLOR_BALL3, COLOR_BALL4, COLOR_BALL5};

int i, n = 33, m = 3, rand_ball, rotate, insidepond = 0, pond_touch = 0, c;

Timer t60(1.0 / 60);

void tick_input(GLFWwindow *window)
{
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);

    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
}

void draw()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;

    i = 0;

    while(i < n)
    {
        ball[i].draw(VP);

        i++;
    }

    i = 0;

    while(i < 4)
    {
        ground[i].draw(VP);

        i++;
    }

    for(i = 0; i < m; i++)
    {
        plank[i].draw(VP);
    }

    pond.draw(VP);

    tramp.draw(VP);

    player.draw(VP);

}

void tick_elements()
{
    if(player.position.x <= 3.8 && player.position.x >= 2)
    {
        //if(player.position.y >= )
        player.position.x -= .009;
    }

    else if(player.position.x <= 2 && player.position.x >= 0)
    {
        player.position.x -= .007;
    }

    else if(player.position.x <= 0 && player.position.x >= -3.8)
    {
        player.position.x -= .002;
    }

    for(i = 0; i < n; i++)
    {
        ball[i].tick();
    }

    player.tick(insidepond);

    i = 0;

    do{
        if (detect_collision(player.bounding_box(), ball[i].bounding_box()) && player.gravityspeed < 0)
        {
            ball[i].position.x = -10;

            player.jump(0);

            player.score += 10;

            cout << endl << "Player Score is: " << player.score << endl;
        }

        i++;
    }

    while(i < n);

    i = 0;

    while(i < m)
    {
        plank[i].tick();

        i++;
    }
}

void refresh()
{
    i = 0;

    do
    {
        if(ball[i].position.x - ball[i].radius > 8)
        {
            ball[i].position.x = -8;

            if(ball[i].nplank != -1)
            {
                plank[ball[i].nplank].position.x = ball[i].position.x + ball[i].radius*cos(2*pi*ball[i].angle);
            }
        }

        i++;
    }

    while(i < n);
}

void initGL(GLFWwindow *window, int width, int height)
{
    player = Player(-6, -4, 0.5, COLOR_MAGNET);

    i = 0;

    do
    {
        y = (rand() % 100000 + 1 - 29000) * 0.0001;

        x = (rand() % 200000 + 1 - 100000) * 0.0001;

        c =rand() % 7;

        r = (rand() % 400 + 400) * 0.001;

        ball[i] = Ball(x, y, r, color[c] );

        ball[i].speed = (rand() % 400 + 400)*(-0.0001);

        i++;
    }

    while(i < n);

    ground[0] = Ground(0, -1, COLOR_GREEN);

    i = 1;

    while(i < 4)
    {
         ground[i] = Ground(0, -i - 1, COLOR_BROWN);

         i++;
    }

    pond = Pond(-1, -4, 2.5, COLOR_BLUE);

    tramp = Trampoline(6, -2.7, COLOR_DARK_RED);


    i = 0;

    while(i < m)
    {
        rand_ball = rand() % n;

        while(ball[rand_ball].nplank!=-1)
        {
            rand_ball = rand() % n;
        }

        angle = (rand() % 45 + 2) * 0.01;

        pl_y = ball[rand_ball].position.y + ball[rand_ball].radius*sin(2*pi*angle);

        pl_x = ball[rand_ball].position.x + ball[rand_ball].radius*cos(2*pi*angle);

        pl_w = (rand() % 400 + 200) * 0.001;

        pl_l = (rand() % 3000 + 4000) * 0.001;

        ball[rand_ball].angle = angle;

        ball[rand_ball].nplank = i;

        plank[i] = Plank(pl_x, pl_y, pl_l, pl_w, COLOR_GREEN);

        plank[i].rotation = 360*angle - 90;

        plank[i].speed = ball[rand_ball].speed;

        i++;
    }

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");

    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {

    srand(time(0));

    int width  = 800,height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    while (!glfwWindowShouldClose(window))
    {

        if (t60.processTick()) {

            draw();

            glfwSwapBuffers(window);

            tick_elements();

            refresh();

            tick_input(window);

            in_water();

            on_tramp();
        }

        glfwPollEvents();
    }

    cout << endl << player.score << endl;

    quit(window);
}

void move_right()
{
    player.right(insidepond);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < 0.8) && ((a.y - b.y) * 2 < (a.height + b.height) && (a.y - b.y)>0);
}

void move_up()
{
    pond_touch = 0;

    if(player.position.y - player.radius <= -4)
    {
        player.jump(0);
    }
}

void move_left()
{
    player.left(insidepond);
}

void on_tramp()
{
    if(player.gravityspeed < 0 && player.position.x >= 4.7 && player.position.x <= 7.3 && player.position.y-player.radius <= -2.7)
    {
        player.jump(1);
    }
}

void in_water()
{
    float right = pond.position.x + 2.5;

    float left = pond.position.x - 2.5;

    float p_radius = 2.5 - player.radius;

    if(player.position.x > left && player.position.x < right && player.position.y -player.radius <=-4 && insidepond==0)
    {
        insidepond = 1;

        if(right - player.radius < player.position.x)
        {
            player.position.y = -4;

            player.position.x = 0.9;

            pond_touch = 1;
        }

        if(left + player.radius > player.position.x)
        {
            player.position.x = -2;

            pond_touch = 1;

            player.position.y = -4;

        }
    }

    if(insidepond && !pond_touch)
    {
        p_x = pond.position.x - player.position.x;

        player.position.y -= 0.04;

        p_y = pond.position.y - pow(sq_y, 0.5) ;

        sq_y = p_radius*p_radius - p_x*p_x;

        if(player.position.y <= p_y)
        {
            player.position.y = p_y;

            pond_touch = 1;
        }
    }

    if(insidepond && pond_touch && player.position.y - player.radius > pond.position.y - 2.5)
    {
        if(player.position.x > pond.position.x)
        {
            player.position.x -= 0.02;
        }

        else
        {
            player.position.x += 0.02;
        }
    }

    if(pond_touch)
    {
        sq_y = p_radius*p_radius - p_x*p_x;

        player.position.y = pond.position.y - pow(sq_y, 0.5) ;

        p_x = pond.position.x - player.position.x;

    }


    if(insidepond)
    {
        if(right - player.radius <= player.position.x)
        {
            player.position.x = right;

            player.position.y = -4 + player.radius;

        }

        if(left + player.radius >= player.position.x)
        {
            player.position.x = left;

            player.position.y = -4 + player.radius;
        }
    }

    if(player.position.x <= left || player.position.x >= right || player.position.y-player.radius>-4)
    {
        pond_touch = 0;

        insidepond = 0;
    }
}

void reset_screen() {
    float bottom = s_c_y - 8 / screen_zoom;
    float top    = s_c_y + 8 / screen_zoom;
    float right  = s_c_x + 8 / screen_zoom;
    float left   = s_c_x - 8 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
