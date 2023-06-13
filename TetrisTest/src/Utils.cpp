#include "Utils.h"
#include <gl/freeglut.h>

namespace GraphUtils 
{

	float colors[][4] = {
		{1, 1, 1},
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		{0.862, 0.078, 0.235},
		{0.780, 0.082, 0.521},
		{1, 0.647, 0},
		{0.854, 0.439, 0.839},
		{0.415, 0.352, 0.803},
		{0.235, 0.701, 0.443}
	};

	void drawString(void* font, const unsigned char* text, float x, float y)
	{
		glRasterPos2f(x, y);
		glutBitmapString(font, text);
	}
}
