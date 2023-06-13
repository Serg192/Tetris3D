#include "IFigure.h"

namespace Tetris {
	IFigure::IFigure()
	{	
	}
	void IFigure::build()
	{
		this->figureCoords.push_back({ Vector2f(0, 2), Vector2f(1, 2), Vector2f(2, 2), Vector2f(3, 2) });
		this->figureCoords.push_back({ Vector2f(1, 0), Vector2f(1, 1), Vector2f(1, 2), Vector2f(1, 3) });
		this->create();
	}
}