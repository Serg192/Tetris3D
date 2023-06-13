#include "SFigure.h"

namespace Tetris {
	SFigure::SFigure()
	{
	}

	void SFigure::build()
	{
		this->figureCoords.push_back({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(2, 1) });
		this->figureCoords.push_back({ Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1), Vector2f(0, 2) });
		this->create();
	}
}