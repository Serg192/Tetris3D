#ifndef Figure_h
#define Figure_h

#include <vector>
#include <ctime>

#include "../Vector2f.h"
#include "../Cube.h"
#include "../Constants.h"
#include "../Utils.h"

namespace Tetris {
	class Figure
	{
	protected:
		int rotationState = 0;
		int xOffset = FIELD_WIDTH / 2;
		int yOffset = FIELD_HEIGHT - 3;

		std::vector<std::vector<Vector2f>> figureCoords;
		std::vector<Cube*> blocks;

	public:
		//Figure(std::vector<std::vector<Vector2f>> figureCoords);
		Figure();
		void freeMemory();
		void rotate();
		bool canMove(Vector2f direction, Cube*** cells);
		bool canRotate(Cube*** cells);
		void update();

		std::vector<Cube*> getAllCubes();

		virtual void build() = 0;

		void move(int x, int y);
		void draw();

	protected:
		void create();

	};
}

#endif



