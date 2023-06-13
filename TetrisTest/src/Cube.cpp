#include <gl/glut.h>
#include <iostream>
#include "Cube.h"

Tetris::Cube::Cube(float xPos, float yPos, float zPos, float size, float color[])
	:xPos(xPos), yPos(yPos), zPos(zPos), size(size), color(color)
{
}


Tetris::Cube::Cube()
{
}

Vector2f Tetris::Cube::getPosition()
{
    return Vector2f(xPos, yPos);
}

void Tetris::Cube::setPosition(float xPos, float yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
}

void Tetris::Cube::setColor(float* color)
{
    this->color = color;
}

void Tetris::Cube::draw()
{
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glColor3f(color[0], color[1], color[2]);
    glutSolidCube(size);
    glPopMatrix();
}
