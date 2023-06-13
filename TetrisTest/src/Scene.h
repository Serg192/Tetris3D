#ifndef Scane_h
#define Scene_h

#include <vector>
#include <ctime>
#include "Cube.h"
#include "PlayField.h"
//#include "FigureInfoGenerator.h"
#include "Figures/Figure.h"
#include "Figures/IFigure.h"
#include "Figures/OFigure.h"
#include "Figures/TFigure.h"
#include "Figures/LFigure.h"
#include "Figures/JFigure.h"
#include "Figures/SFigure.h"
#include "Figures/ZFigure.h"

namespace Tetris
{
	class Scene
	{
	private:
		PlayField field;
		//FigureInfoGenerator* infoGen;
		Figure* currentFigure = nullptr;

		bool pause = true;
		bool gameOver = false;

		int score;
		char scoreText[20];

		long timer_start_time;

		float distZ;
		float angleX, angleY;
		float mouseX, mouseY;
		int mouseBtn;

	private:
		void update();
		void show();
		
	public:
		void init();
		~Scene();
		void display();
		void restart();
		void onMotion(int x, int y);
		void onMouse(int button, int state, int x, int y);
		void userKeyboardInput(unsigned char key, int x, int y);

		void genFigure();
	};
}

#endif