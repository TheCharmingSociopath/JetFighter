#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "sphere.h"
#include "sea.h"
#include "island.h"
#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Airplane plane;
Sea sea;
vector <Island> islands;

float jet_x = 0, jet_y = 30, jet_z = 0, jet_rot_x = 0, jet_rot_y = 0, jet_rot_z = 1;
float screen_center_x = jet_x, screen_center_y = jet_y, screen_center_z = jet_z;
float camera_center_x = 0, camera_center_y = 40, camera_center_z = -10;
float up_x = 0, up_y = 1, up_z = 0;
float camera_rotation_angle = 0, screen_zoom = 1;
float fovy = 45.0f, aspect = 1.0f, zNear = 0.1f, zFar = 500.0f;
int camera_modes = 0;
/*  0: follow-cam view
    1: tower view
    2: top view
    3: plane view
    4: helicopter-cam view
*/
bool cam_press;
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

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);
    plane.draw(VP, jet_rot_x, jet_rot_y, jet_rot_z);
    for (int i=0; i<islands.size(); ++i)
        islands[i].draw(VP);
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
        jet_z += 0.2 * cos(plane.rotation.y * M_PI/180.0f);
        jet_x += 0.2 * sin(plane.rotation.y * M_PI/180.0f);
    }
    if (back) {
        jet_z -= 0.2 * cos(plane.rotation.y * M_PI/180.0f);
        jet_x -= 0.2 * sin(plane.rotation.y * M_PI/180.0f);
    }
    if (up) {
        jet_y += 0.2;
    }
    if (down) {
        jet_y -= 0.2;
    }
    if (q) {
        plane.rotation.y += 0.5f;
    }
    if (e) {
        plane.rotation.y -= 0.5f;
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
    plane.tick();
    camera_tick();
    plane.set_position(jet_x, jet_y, jet_z);
    sea.tick();
    for (int i=0; i<islands.size(); ++i)
    {
        islands[i].tick();
    }
    generate_objects();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Airplane(jet_x, jet_y, jet_z, COLOR_RED, 5, 0, 1, 4);
    sea = Sea(0, 0, 0, COLOR_SEA);
    islands.push_back( Island(jet_x, jet_z + 50, COLOR_ISLAND) );

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
    int width  = 600;
    int height = 600;

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
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(fovy, aspect, zNear, zFar);
}

/*  0: follow-cam view
    1: tower view
    2: top view
    3: plane view
    4: helicopter-cam view
*/

void camera_tick()
{
    cout << "CM " << camera_modes << endl;
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
            screen_center_x = jet_x;
            screen_center_y = jet_y;
            screen_center_z = jet_z;
            break;
        case 3:
            screen_center_x = jet_x;
            screen_center_y = jet_y;
            screen_center_z = jet_z + 10;
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
            up_x = 0;
            up_y = 0;
            up_z = 1;
            break;
    }

    switch (camera_modes) //camera center
    {
        case 0:
            camera_center_x = jet_x;
            camera_center_y = jet_y + 10;
            camera_center_z = jet_z - 20;
            break;
        case 1:
            camera_center_x = jet_x + 20;
            camera_center_y = jet_y + 20;
            camera_center_z = jet_z - 20;
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
    // cout << "CC " <<  camera_center_x << " " << camera_center_y <<  " " << camera_center_z << endl;
    // cout << "SC " << screen_center_x << " " << screen_center_y <<  " " << screen_center_z << endl;
}

void generate_objects()
{
    for (int i=0; i<4000; i += 25)
    {
        islands.push_back(Island (i * 25, i * 25, COLOR_ISLAND));
    }
}