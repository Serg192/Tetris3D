#ifndef Cube_h
#define Cube_h
#include "Vector2f.h"

namespace Tetris
{
	class Cube
	{
	private:
		float xPos, yPos, zPos;
		float size;
		float* color;

	public:
		Cube();
		Cube(float xPos, float yPos, float zPos, float size, float* color);

		Vector2f getPosition();
		void setPosition(float xPos, float yPos);
		void setColor(float* color);


		void draw();

	};
}
#endif
