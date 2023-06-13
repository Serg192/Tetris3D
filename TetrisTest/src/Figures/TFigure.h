#ifndef TFigure_h
#define TFigure_h

#include "Figure.h"

namespace Tetris {
	class TFigure : public Figure
	{
	public:
		TFigure();
		void build() override;
	};
}

#endif
