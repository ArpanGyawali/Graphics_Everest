#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <stb/stb_image.h>
#include "Pipeline.h"

#define WIDTH 1000
#define HEIGHT 800

float deltaTime = 0.0f;
float lastFrame = 0.0f;
//Camera camera(Vec3f(0.0f, 0.0f, 1.0f));
//ZBuffer zb(WIDTH, HEIGHT);

Pipeline pipeline;
bool isMix = true;
int fileid=0;

void myinit(void)
{

    glViewport(0, 0, WIDTH, HEIGHT);
    //glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    //gluOrtho2D(0, 1, 0, 1);
    //gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);

    //Handle Timing
    float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

GLuint tex;
unsigned char* texture_data;

void loadTexture() {
    int w, h;
    stbi_set_flip_vertically_on_load(true);
    if(fileid == 1)
        texture_data = stbi_load("OBJFiles/back2.jpg", &w, &h, nullptr, 4);
    else if(fileid == 2)
        texture_data = stbi_load("OBJFiles/back3.jpg", &w, &h, nullptr, 4);
    else if(fileid == 3)
        texture_data = stbi_load("OBJFiles/back5.jpg", &w, &h, nullptr, 4);

    if (texture_data != NULL) {
        std::cout << "background loaded" << std::endl;
    }
    //upload to GPU texture

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texture_data);
}

void drawModel() {
    pipeline.update();
}

void background() {
    //glClear(GL_COLOR_BUFFER_BIT);

    /*glBegin(GL_POLYGON);
    glColor3f(1.0, 0.83, 0.50);
    glVertex2d(0, 0);
    glColor3f(0.6, 1.0, 1.0);
    glVertex2d(0, 800);
    glColor3f(0.6, 1.0, 1.0);
    glVertex2d(1000, 800);
    glColor3f(1.0, 0.83, 0.50);
    glVertex2d(1000, 0);
    glEnd();*/
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 1); glVertex2i(0, 800);
    glTexCoord2i(1, 1); glVertex2i(1000, 800);
    glTexCoord2i(1, 0); glVertex2i(1000, 0);
    glTexCoord2i(0, 0); glVertex2i(0, 0);
    glEnd();
    if (!isMix) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void specialKeyboard(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        pipeline.ProcessKeyboard(Camera_Movement::UP, deltaTime);
        break;
    case GLUT_KEY_DOWN:
        pipeline.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
        break;
    case GLUT_KEY_LEFT:
        pipeline.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
        break;
    case GLUT_KEY_RIGHT:
        pipeline.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
        break;
    default:
        break;
    }
    glutPostRedisplay();  //Window redraw
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'W':
        pipeline.ProcessKeyboard(Camera_Movement::WKEY, deltaTime);
        break;
    case 'S':
        pipeline.ProcessKeyboard(Camera_Movement::SKEY, deltaTime);
        break;
    case 'A':
        pipeline.ProcessKeyboard(Camera_Movement::AKEY, deltaTime);
        break;
    case 'D':
        pipeline.ProcessKeyboard(Camera_Movement::DKEY, deltaTime);
        break;
    case 'Z':
        pipeline.ProcessKeyboard(Camera_Movement::ZKEY, deltaTime);
        break;
    case 'X':
        pipeline.ProcessKeyboard(Camera_Movement::XKEY, deltaTime);
        break;
    case 'C':
        pipeline.ProcessKeyboard(Camera_Movement::CKEY, deltaTime);
        break;
    case 'V':
        pipeline.ProcessKeyboard(Camera_Movement::VKEY, deltaTime);
        break;
    case 'R':
        pipeline.ProcessKeyboard(Camera_Movement::RKEY, deltaTime);
        break;
    case 'T':
        pipeline.ProcessKeyboard(Camera_Movement::TKEY, deltaTime);
        break;
    case 'Y':
        pipeline.ProcessKeyboard(Camera_Movement::YKEY, deltaTime);
        break;
    case 'F':
        pipeline.ProcessKeyboard(Camera_Movement::FKEY, deltaTime);
        break;
    case 'G':
        pipeline.ProcessKeyboard(Camera_Movement::GKEY, deltaTime);
        break;
    case 'H':
        pipeline.ProcessKeyboard(Camera_Movement::HKEY, deltaTime);
        break;
    case 'P':
        pipeline.ProcessKeyboard(Camera_Movement::PKEY, deltaTime);
        break;
    case 'M':
        if (isMix)
            isMix = false;
        else
            isMix = true;
        break;
    case 49:            //num 1
        fileid = 1;
        break;
    case 50:            //num 2
        fileid = 2;
        break;
    case 51:            //num 3
        fileid = 3;
        break;
    case 27:    //ESC key
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();  //Window redraw
}


void display()
{
    //glClearColor(1.0, 1.0, 1.0, 1.0);
    ////  Clear screen and Z-buffer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //drawCube();
    //drawSphere();
    loadTexture();
    background();
    

    drawModel();

    glFlush();
    glutSwapBuffers();
    //glFlush();
    

}

int main(int argc, char* argv[]) {
    /*Vec3f texture = GetPixel(99, 99);
    std::cout << texture.x << texture.y << texture.z << getWidth() << getHeight() << std::endl;*/

    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(WIDTH, HEIGHT);
    //glutInitWindowPosition(0, 0);


    // Create window
    glutCreateWindow("Mount Everest");

    //  Enable Z-buffer depth test
    //glEnable(GL_DEPTH_TEST);
    //loadTexture();
    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    //glutIdleFunc(drawLine);
    myinit();
    //  Pass control to GLUT for events
    glutMainLoop();

    //  Return to OS
    return 0;

}
