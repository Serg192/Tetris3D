#ifndef ZFigure_h
#define ZFigure_h

#include "Figure.h"

namespace Tetris {
	class ZFigure : public Figure
	{
	public:
		ZFigure();
		void build() override;
	};
}

#endif


