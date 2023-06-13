#include "JFigure.h"

namespace Tetris {
	JFigure::JFigure()
	{
	}

	void JFigure::build()
	{
		figureCoords.push_back({ Vector2f(0, 1), Vector2f(0, 2), Vector2f(1, 1), Vector2f(2, 1) }); //0
		figureCoords.push_back({ Vector2f(1, 0), Vector2f(1, 1), Vector2f(1, 2), Vector2f(2, 2) });  //1
		figureCoords.push_back({ Vector2f(0, 1), Vector2f(1, 1), Vector2f(2, 1), Vector2f(2, 0) });
		figureCoords.push_back({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(1, 2) });

		create();
	}
}

