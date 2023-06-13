#ifndef OFigure_h
#define OFigure_h
#include "Figure.h"

namespace Tetris {
	class OFigure : public Figure {
	public:
		OFigure();
		void build() override;
	};
}

#endif
