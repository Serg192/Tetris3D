#ifndef JFigure_h
#define JFigure_h

#include "Figure.h"

namespace Tetris {
	class JFigure : public Figure
	{
	public:
		JFigure();
		void build() override;
	};
}

#endif


