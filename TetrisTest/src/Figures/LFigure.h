#ifndef LFigure_h
#define LFigure_h
#include "Figure.h"

namespace Tetris {
	class LFigure : public Figure {
	public:
		LFigure();
		void build() override;
	};
}

#endif