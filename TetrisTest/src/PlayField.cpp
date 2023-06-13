#include "PlayField.h"
#include "Utils.h"

void Tetris::PlayField::init()
{
	elements = new Cube** [FIELD_WIDTH];

	for (int i = 0; i < FIELD_WIDTH; i++) {
		elements[i] = new Cube * [FIELD_HEIGHT];
		for (int j = 0; j < FIELD_HEIGHT; j++)
			elements[i][j] = nullptr;
	}

	buildPlayField();
}

void Tetris::PlayField::draw()
{
	
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			if (elements[x][y] != nullptr)
				elements[x][y]->draw();
		}
	}
	
}

Tetris::Cube*** Tetris::PlayField::getCellsInfo()
{
	return elements;
}

//Додає блоки фігури, що щойно приземлилася, до масиву ігрового поля
//змінюючи їх колір на зелений. Якщо операція пройшла успішно, то повертає
// 0, якщо при додаванні виявилося, що додані блоки не поміщаються в ігрове
//поле - повертає -1 
int Tetris::PlayField::addCubesToStack(std::vector<Cube*> cubes)
{
	for (Cube* cube : cubes) {
		Vector2f pos = cube->getPosition();
		pos.x = pos.x / (BLOCK_SIZE + SPACING);
		pos.y = pos.y / (BLOCK_SIZE + SPACING);

		//cube->setColor(GraphUtils::colors[GraphUtils::Color::GREEN]);

		elements[(int)(pos.x + 0.5f)][(int)(pos.y + 0.5f)] = cube;
		if ((int)(pos.y + 0.5f) >= FIELD_HEIGHT - 1) {
			return -1;
		}
	}

	return 0;
}

//Перевіряє та очищує рядки ігрового поля, якщо виявилося, що вони заповнені блоками
//повертає кількість очищених рядків
int Tetris::PlayField::checkForFullLines()
{
	int cleared = 0;
	bool shouldClearLine = false;
	for (int y = 1; y < FIELD_HEIGHT - 1; y++) {
		shouldClearLine = false;
		for (int x = 1; x < FIELD_WIDTH - 1; x++) {
			if (elements[x][y] == nullptr) {
				shouldClearLine = false;
				break;
			}
			shouldClearLine = true;
		}
		
		if (cleared > 0 && !shouldClearLine) {
			for (int xi = 1; xi < FIELD_WIDTH - 1; xi++) {
				if (elements[xi][y] != nullptr) {
					float nx = xi * BLOCK_SIZE + xi * SPACING;
					float ny = (y - cleared) * BLOCK_SIZE + (y - cleared) * SPACING;
				
					elements[xi][y - cleared] = elements[xi][y];
					elements[xi][y] = nullptr;
					elements[xi][y - cleared]->setPosition(nx, ny);
				}
			}
		}

		if (shouldClearLine) {
			for (int xi = 1; xi < FIELD_WIDTH - 1; xi++) {
				delete elements[xi][y];
				elements[xi][y] = nullptr;
			}
			cleared++;
		}
	}

	return cleared;
}

void Tetris::PlayField::restart()
{
	freeMemory();
	init();
}

//Будування ігрового поля
void Tetris::PlayField::buildPlayField()
{
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		elements[0][i] = new Cube(0, i * BLOCK_SIZE + SPACING * i, 0, BLOCK_SIZE, GraphUtils::colors[GraphUtils::Color::WHITE]);
		elements[FIELD_WIDTH - 1][i] = new Cube((FIELD_WIDTH - 1) * BLOCK_SIZE + SPACING * (FIELD_WIDTH - 1), i * BLOCK_SIZE + SPACING * i, 0, BLOCK_SIZE, GraphUtils::colors[GraphUtils::Color::WHITE]);
	}
	
	for (int i = 1; i < FIELD_WIDTH - 1; i++) {
		elements[i][0] = new Cube(i * BLOCK_SIZE + i * SPACING, 0, 0, BLOCK_SIZE, GraphUtils::colors[GraphUtils::Color::WHITE]);
		elements[i][FIELD_HEIGHT - 1] = new Cube(i * BLOCK_SIZE + i * SPACING, (FIELD_HEIGHT - 1) * BLOCK_SIZE + SPACING * (FIELD_HEIGHT - 1), 0, BLOCK_SIZE, GraphUtils::colors[GraphUtils::Color::WHITE]);
	}
}

//Очищення масиву елементів поля
void Tetris::PlayField::freeMemory()
{
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			if (elements[x][y] != nullptr) delete elements[x][y];
		}
		delete[] elements[x];
	}

	delete elements;
}

Tetris::PlayField::~PlayField()
{
	freeMemory();
}
