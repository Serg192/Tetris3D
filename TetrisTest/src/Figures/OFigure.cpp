#include "OFigure.h"

namespace Tetris {
	OFigure::OFigure()
	{
	}

	void OFigure::build()
	{
		this->figureCoords.push_back({ Vector2f(0, 1), Vector2f(0, 2), Vector2f(1, 1), Vector2f(1, 2) });
		this->create();
	}
}
