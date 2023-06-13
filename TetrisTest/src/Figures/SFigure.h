#ifndef SFigure_h
#define SFigure_h
#include "Figure.h"

namespace Tetris {
	class SFigure : public Figure {
	public:
		SFigure();
		void build() override;
	};
}

#endif