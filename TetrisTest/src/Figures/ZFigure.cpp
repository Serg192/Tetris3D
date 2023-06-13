#include "ZFigure.h"

namespace Tetris {
	ZFigure::ZFigure()
	{
	}

	void ZFigure::build()
	{
		this->figureCoords.push_back({ Vector2f(0, 1), Vector2f(1, 1), Vector2f(1, 0), Vector2f(2, 0) });
		this->figureCoords.push_back({ Vector2f(0, 0), Vector2f(0, 1), Vector2f(1, 1), Vector2f(1, 2) });
		this->create();
	}
}
