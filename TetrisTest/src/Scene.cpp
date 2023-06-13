#include <gl/glut.h>
#include "Scene.h"
#include "Utils.h"

void Tetris::Scene::update()
{
        sprintf(scoreText, "SCORE: %d", score);

        if (!pause) {
            long now = clock();
            double elapsed = ((double)now - timer_start_time) / CLOCKS_PER_SEC;
            //Оновлення поля гри відбувається згідно із швидкістю гри
            if (elapsed >= GAME_SPEED) {
                //Якщо фігура може рухатися вниз, додаємо її до об'єктів ігрового поля
                if (currentFigure->canMove(Vector2f(0, -1), field.getCellsInfo())) {
                    currentFigure->move(0, -1);
                }
                else {
                    //Якщо сталоля переповнення ігрового поля, то це означає кінець гри 
                    //Гра ставиться на паузу
                    if (field.addCubesToStack(currentFigure->getAllCubes()) == -1) {
                        gameOver = true;
                        pause = true;
                    }
                    // Генерація нової фігури після її додавання до ігрового поля
                    genFigure();

                    if (int cleared = field.checkForFullLines() != 0) {
                        //Якщо гравець склав повну лінію, то до рахунку додається 100 * кількість складених ліній балів
                        score += 100 * cleared;
                    }
                    else {
                        //Якщо фігура просто приземлилася, то до рахунку додається 10 балів
                        score += 10;
                    }

                }
                timer_start_time = now;
            }
        }
}

void Tetris::Scene::show()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //Вмикаємо те, що стосується освітлення
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

  
    //////Відображення тексту
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)scoreText, 0.02f, 0.95f);

    GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"WASD to move", 0.02f, 0.90f);
    GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"SPACE to rotate", 0.02f, 0.85f);
    GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Z to zoom in", 0.02f, 0.80f);
    GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"X to zoom out", 0.02f, 0.75f);

    if (pause)
        GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press SPACE to start the game", 0.3f, 0.05f);
    if (gameOver)
        GraphUtils::drawString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"GAME OVER", 0.4f, 0.1f);

    glPopMatrix();
    ////////////////

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //В разі зміни розміру вікна 
    //пристосовуємо координатну систему
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-5, -10, distZ);
    glRotatef(angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(angleY, 1.0f, 0.0f, 0.0f);

    field.draw();

    if(!pause)
         currentFigure->draw();
   
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glFlush();

    glutSwapBuffers();
}

void Tetris::Scene::init()
{

    field.init();

    timer_start_time = clock();

    genFigure();

    score = 0;
    distZ = -30;
    angleX = 0;
    angleY = 0;

    srand(time(NULL));
}

Tetris::Scene::~Scene()
{
    if(currentFigure != nullptr)
        delete currentFigure;
    //delete infoGen;
}

void Tetris::Scene::display()
{
    update();
    show();
}

void Tetris::Scene::restart()
{
    //Скидаємо значення змінних
    score = 0;
    gameOver = false;

    //Генеруємо нову фігуру
    currentFigure->freeMemory();
    genFigure();

    //Перезапускаємо ігрове поле
    field.restart();
}

void Tetris::Scene::userKeyboardInput(unsigned char key, int x, int y)
{
    switch (key) {
  
    //SPACE
    case 32: 
        if (pause) {
            pause = false;
            if (gameOver) {
                gameOver = false;
                restart();
            }
        }
        if (currentFigure->canRotate(field.getCellsInfo())) {
            currentFigure->rotate();
        }
         break;
    //DOWN
    case 's': 
        while (currentFigure->canMove(Vector2f(0, -1), field.getCellsInfo())) {
            currentFigure->move(0, -1);
        }
        break;
  
    //LEFT
    case 'a': 
            if (currentFigure->canMove(Vector2f(-1, 0), field.getCellsInfo())) {
                currentFigure->move(-1, 0);
            }
         break;
    //RIGHT
    case 'd':
        if (currentFigure->canMove(Vector2f(1, 0), field.getCellsInfo())) {
            currentFigure->move(1, 0);
        }
        break;

    //ZOOM IN
    case 'z': 
        if (distZ <= -20)
            distZ += 1;
        break;
    //ZOOM OUT
    case 'x':
        if (distZ >= -35)
            distZ -= 1;
        break;
    }
}

void Tetris::Scene::onMotion(int x, int y)
{
    if (mouseBtn == 0) {
        angleX += x - mouseX;
        angleY += y - mouseY;
        mouseX = x;
        mouseY = y;
    }
}

void Tetris::Scene::genFigure()
{
    if (currentFigure != nullptr)
        delete currentFigure;

    int des = rand() % 7;

    switch (des) {
    case 0: currentFigure = new OFigure(); break;
    case 1: currentFigure = new IFigure(); break;
    case 2: currentFigure = new SFigure(); break;
    case 3: currentFigure = new TFigure(); break;
    case 4: currentFigure = new LFigure(); break;
    case 5: currentFigure = new JFigure(); break;
    case 6: currentFigure = new ZFigure(); break;
    }
    
    currentFigure->build();
}



//Оновлення координат миші та значення натиснутої кнопки
void Tetris::Scene::onMouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;
    mouseBtn = button;
}
