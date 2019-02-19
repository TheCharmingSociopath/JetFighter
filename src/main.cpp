#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "sphere.h"
#include "sea.h"
#include "island.h"
#include "score.h"
#include "cannon.h"
#include "arrow.h"
#include "ring.h"
#include "parachute.h"

#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Airplane plane;
Sea sea;
Arrow arrow;
vector <Island> islands;
Score p_score, p_fuel, p_altitude, p_speed;
vector <Cannon> cannon;
vector <Ring> rings;
vector <Parachute> parachutes;

float jet_x = 0, jet_y = 100, jet_z = 0, jet_rot_x = 0, jet_rot_y = 0, jet_rot_z = 1;
float screen_center_x = jet_x, screen_center_y = jet_y, screen_center_z = jet_z;
float camera_center_x = 0, camera_center_y = 40, camera_center_z = -10;
float up_x = 0, up_y = 1, up_z = 0;
float camera_rotation_angle = 0, screen_zoom = 1;
float arrow_rot = 0, arrow_x = (screen_center_x + camera_center_x) / 2,
arrow_y = (screen_center_y + camera_center_y) / 2,
arrow_z = (screen_center_z + camera_center_z) / 2;

float fovy = 45.0f, aspect = 1.0f, zNear = 0.1f, zFar = 500.0f;
int camera_modes = 0, score = 0, fuel = 100, altitude = jet_y, cannon_fire_time;
int ISLANDS_NUMBER = 80, active_island;

/*  0: follow-cam view
    1: tower view
    2: top view
    3: plane view
    4: helicopter-cam view
*/
bool cam_press, cannon_active = false;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( camera_center_x, camera_center_y, camera_center_z );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (screen_center_x, screen_center_y, screen_center_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 ortho_VP = Matrices.ortho_projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    arrow.draw(VP, arrow_rot);
    plane.draw(VP, jet_rot_x, jet_rot_y, jet_rot_z);
    for (int i=0; i<islands.size(); ++i)
    {
        islands[i].draw(VP);
    }
    for (int i=0; i<rings.size(); ++i)
    {
        rings[i].draw(VP);
    }
    for (int i=0; i<parachutes.size(); ++i)
    {
        parachutes[i].draw(VP);
    }
    for (int i=0; i<cannon.size(); ++i)
    {
        cannon[i].draw(VP);
        // cout << cannon[i].position.x << " " << cannon[i].position.y << " " << cannon[i].position.z << endl;
    }
    p_score.set_position(0, 30, 0);
    p_score.print_score(score, ortho_VP);
    p_fuel.set_position(screen_center_x - 4, screen_center_y - 4, screen_center_z);
    p_fuel.print_score(score, ortho_VP);
    p_altitude.set_position(screen_center_x + 4, screen_center_y - 4, screen_center_z);
    p_altitude.print_score(score, ortho_VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int back = glfwGetKey(window, GLFW_KEY_S);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int cam = glfwGetKey(window, GLFW_KEY_C);
    int down = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);

    if (left) {
        plane.rotation.z -= 0.5f;
    }
    if (right) {
        plane.rotation.z += 0.5f;
    }
    if (forward) {
        jet_z += 1.0f * cos(plane.rotation.y * M_PI/180.0f);
        jet_x += 1.0f * sin(plane.rotation.y * M_PI/180.0f);
    }
    if (back) {
        jet_z -= 1.0f * cos(plane.rotation.y * M_PI/180.0f);
        jet_x -= 1.0f * sin(plane.rotation.y * M_PI/180.0f);
    }
    if (up) {
        jet_y += 0.5;
    }
    if (down) {
        jet_y -= 0.5;
    }
    if (q) {
        plane.rotation.y += 0.8f;
    }
    if (e) {
        plane.rotation.y -= 0.8f;
    }
    if (cam) {
        cam_press = true;
    }
    else if (cam_press) {
        camera_modes = (camera_modes + 1) % 4;
        cam_press = false;
    }
}

void tick_elements() {
    altitude = jet_y;
    plane.tick();
    camera_tick();
    plane.set_position(jet_x, jet_y, jet_z);
    sea.tick();
    if (t60.seconds % 15 == 0 && t60.count == 0)
    {
        parachutes.push_back(Parachute (plane.position.x + 50, plane.position.z + 50));
        parachutes.push_back(Parachute (plane.position.x + 50, plane.position.z - 50));
        parachutes.push_back(Parachute (plane.position.x - 50, plane.position.z + 50));
        parachutes.push_back(Parachute (plane.position.x - 50, plane.position.z - 50));
    }
    if (t60.seconds % 2 == 0 and t60.count == 0)
    {
        parachutes.push_back(Parachute (rand() % 1000, rand() % 1000));
        rings.push_back( Ring(rand() % 1000, rand() % 100, rand() % 1000) );
    }

    if (t60.seconds % 2 == 0 and t60.count == 0)
    {
        ++score;
        --fuel;
    }
    for (int i=0; i<parachutes.size(); ++i)
    {
        parachutes[i].tick();
        if (parachutes[i].position.y <= 5)
            parachutes.erase(parachutes.begin() + i);
    }
    if (!cannon_active)
    {
        int active_island = rand() % ISLANDS_NUMBER;
        islands[active_island].active = true;
        cannon_active = true;
        islands[active_island].activation_time = t60.seconds;
    }

    for(int i=0; i<rings.size(); ++i)
    {
        if( detect_collision (rings[i].box, plane.box) )
        {
            score += 5;
            rings.erase(rings.begin() + i);
        }
    }

    make_arrow();
    fire_cannon();
    for(int i=0; i<cannon.size(); ++i)
    {
        cannon[i].position.x += 10.0f * sin(cannon[i].theta) * sin(cannon[i].phi);
        cannon[i].position.y += 10.0f * cos(cannon[i].theta);
        cannon[i].position.z += 10.0f * sin(cannon[i].theta) * cos(cannon[i].phi);
        // cout << i << " " << cannon[i].position.x << " " << cannon[i].position.y << " " << cannon[i].position.z << endl;
        // cout << cannon[i].theta << " " << cannon[i].phi << endl;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Airplane(jet_x, jet_y, jet_z, COLOR_RED, 5, 0, 1, 4);
    sea = Sea(0, 0, 0, COLOR_SEA);
    arrow = Arrow(arrow_x, arrow_y, arrow_z);

    for (int i=0; i<ISLANDS_NUMBER / 4; ++i)
    {
        islands.push_back( Island(rand() % 1000, rand() % 1000, COLOR_ISLAND) );
        islands.push_back( Island(rand() % 1000, - (rand() % 1000), COLOR_ISLAND) );
        islands.push_back( Island(-(rand() % 1000), rand() % 1000, COLOR_ISLAND) );
        islands.push_back( Island(-(rand() % 1000), - (rand() % 1000), COLOR_ISLAND) );
    }
    p_score = Score(camera_center_x, camera_center_y, camera_center_z + 5, COLOR_BLACK);
    p_fuel = Score(screen_center_x, screen_center_x, screen_center_z, COLOR_BLACK);
    p_altitude = Score(camera_center_x + 4, camera_center_y - 4, camera_center_z, COLOR_BLACK);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
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
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            tick_elements();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.len_x + b.len_x)) &&
           (abs(a.y - b.y) * 2 < (a.len_y + b.len_y)) &&
           (abs(a.z - b.z) * 2 < (a.len_z + b.len_z));
}

void reset_screen() {
    float top    = screen_center_y + 10 / screen_zoom;
    float bottom = screen_center_y - 10 / screen_zoom;
    float left   = screen_center_x - 10 / screen_zoom;
    float right  = screen_center_x + 10 / screen_zoom;
    Matrices.projection = glm::perspective(fovy, aspect, zNear, zFar);
    Matrices.ortho_projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

/*  0: follow-cam view
    1: tower view
    2: top view
    3: plane view
    4: helicopter-cam view
*/

void camera_tick()
{
    // cout << "CM " << camera_modes << endl;
    switch (camera_modes) //screen center
    {
        case 0:
            screen_center_x = jet_x;
            screen_center_y = jet_y + 5;
            screen_center_z = jet_z;
            break;
        case 1:
            screen_center_x = jet_x;
            screen_center_y = jet_y + 10;
            screen_center_z = jet_z + 5;
            break;
        case 2:
            screen_center_x = jet_x + sin(plane.rotation.y * M_PI / 180);
            screen_center_y = jet_y;
            screen_center_z = jet_z + cos(plane.rotation.y * M_PI / 180);
            break;
        case 3:
            screen_center_x = jet_x + 10 * sin(plane.rotation.y * M_PI / 180);
            screen_center_y = jet_y;
            screen_center_z = jet_z + 10 * cos(plane.rotation.y * M_PI / 180);
            break;
        case 4:
            break;
    }

    switch (camera_modes) //up
    {
        case 0:
        case 1:
        case 3:
        case 4:
            up_x = 0;
            up_y = 1;
            up_z = 0;
            break;
        case 2:
            up_x = sin(plane.rotation.y * M_PI / 180);
            up_y = 0;
            up_z = cos(plane.rotation.y * M_PI / 180);
            break;
    }

    switch (camera_modes) //camera center
    {
        case 0:
            camera_center_x = jet_x  - 20 * sin(plane.rotation.y * M_PI / 180);
            camera_center_y = jet_y + 10;
            camera_center_z = jet_z - 20 * cos(plane.rotation.y * M_PI / 180);
            break;
        case 1:
            camera_center_x = jet_x + 50;
            camera_center_y = jet_y + 20;
            camera_center_z = jet_z - 50;
            break;
        case 2:
            camera_center_x = jet_x;
            camera_center_y = jet_y + 50;
            camera_center_z = jet_z;
            break;
        case 3:
            camera_center_x = jet_x;
            camera_center_y = jet_y;
            camera_center_z = jet_z + (plane.length / 2);
            break;
        case 4:
            /* code */
            break;
    }

    switch (camera_modes) // Arrow's position
    {
        case 0:
            arrow_x = jet_x + 10 * sin(plane.rotation.y * M_PI / 180);
            arrow_y = jet_y;
            arrow_z = jet_z + 10 * cos(plane.rotation.y * M_PI / 180);
            break;
        case 1:
            arrow_x = jet_x;
            arrow_y = jet_y;
            arrow_z = jet_z + 10;
            break;
        case 2:
            arrow_x = jet_x + 10 * sin(plane.rotation.y * M_PI / 180);
            arrow_y = jet_y;
            arrow_z = jet_z + 10 * cos(plane.rotation.y * M_PI / 180);
            break;
        case 3:
            arrow_x = jet_x + 10 * sin(plane.rotation.y * M_PI / 180);
            arrow_y = jet_y;
            arrow_z = jet_z + 10 * cos(plane.rotation.y * M_PI / 180);
            break;
        case 4:
            break;
    }
    
    // cout << "CC " <<  camera_center_x << " " << camera_center_y <<  " " << camera_center_z << endl;
    // cout << "SC " << screen_center_x << " " << screen_center_y <<  " " << screen_center_z << endl;
}

void make_arrow()
{
    arrow.set_position(arrow_x, arrow_y, arrow_z);

    float i_x = islands[active_island].position.x, i_z = islands[active_island].position.z, r,
    i_y = 15;
    r = sqrt(((i_x - arrow_x) * (i_x - arrow_x)) + ((i_y - arrow_y) * (i_y - arrow_y)) + ((i_z - arrow_z) * (i_z - arrow_z)));

    arrow_rot = acos((i_z - arrow_z) / r) * 180 / M_PI;

    if (i_x < arrow_x)
        arrow_rot *= -1.0f;
}

void fire_cannon()
{
    if(t60.seconds - cannon_fire_time < 3)
        return;
    float i_x = islands[active_island].position.x, i_z = islands[active_island].position.z,
    i_y = islands[active_island].position.y,
    r = sqrt(((i_x - jet_x) * (i_x - jet_x)) + ((i_y - jet_y) * (i_y - jet_y)) + ((i_z - jet_z) * (i_z - jet_z))),
    r1 = sqrt(((i_x - jet_x) * (i_x - jet_x)) + ((i_z - jet_z) * (i_z - jet_z)));
    if(r < 400)
    {
        float theta = acos((jet_y - i_y) / r),
        phi = acos((jet_z - i_z) / r1);
        if (i_x > jet_x)
            phi *= -1.0f;
        cannon.push_back( Cannon(i_x, i_y + 75, i_z, theta, phi) );
        cout << jet_x << " " << jet_y << " " << jet_z << " " << i_x << " " <<i_y + 75 << " " << i_z << endl;
        cannon_fire_time = t60.seconds;
    }
}