#ifndef PlayField_h
#define PlayField_h

#include <vector>
#include "Cube.h"
#include "Vector2f.h"
#include "Constants.h"

namespace Tetris
{
	class PlayField
	{
	private:
		//Інформація про клітинки ігрового поля зберігатиметься у
		//двовимірному масиві вказівників на Cube
		Cube*** elements;

	public:
		void init();
		void draw();

		Cube*** getCellsInfo();
		int addCubesToStack(std::vector<Cube*> cubes);
		int checkForFullLines();

		void restart();

		~PlayField();

	private:
		void buildPlayField();
		void freeMemory();
	};
}

#endif
