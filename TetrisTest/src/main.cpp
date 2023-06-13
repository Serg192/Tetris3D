#include <gl/glut.h>
#include "Scene.h"
#include "Constants.h"

Tetris::Scene* scene;

void display()
{
    scene->display();
}

void userKeyboardInput(unsigned char key, int x, int y) {
    scene->userKeyboardInput(key, x, y);
}

void onMotion(int x, int y)
{
    scene->onMotion(x, y);
}

void onMouse(int button, int state, int x, int y) 
{
    scene->onMouse(button, state, x, y);
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char* argv[])
{
    scene = new Tetris::Scene();
    scene->init();
    glutInit(&argc, argv);
    glutInitWindowSize(Tetris::WIDTH, Tetris::HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutKeyboardFunc(userKeyboardInput);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutMotionFunc(onMotion);
    glutMouseFunc(onMouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    delete scene;
    return 0;
}


