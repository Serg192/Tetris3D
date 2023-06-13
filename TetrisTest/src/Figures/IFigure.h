#ifndef IFigure_h
#define IFigure_h
#include "Figure.h"

namespace Tetris {
	class IFigure : public Figure {
	public:
		IFigure();
		void build() override;
	};
}

#endif
