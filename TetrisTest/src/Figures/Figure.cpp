#include "Figure.h"

Tetris::Figure::Figure()
{
	srand(time(NULL));
}

void Tetris::Figure::create()
{
	int color = rand() % MAX_COLORS;
	//Перетворення "згенерованих" координат на об'єкти на сцені
	for (int i = 0; i < figureCoords[rotationState].size(); i++) {
		int x = figureCoords[rotationState][i].x + xOffset;
		int y = figureCoords[rotationState][i].y + yOffset;
	
		blocks.push_back(new Cube(x * BLOCK_SIZE + x * SPACING, y * BLOCK_SIZE + SPACING * y, 0, BLOCK_SIZE, GraphUtils::colors[color]));
	}
}

//Метод викликається перед знищенням екземпляру об'єкта фігури,
//в тому разі, якщо потрібно видалити і блоки з яких складається фігура
void Tetris::Figure::freeMemory()
{
	for (Cube* c : blocks)
		delete c;
}

void Tetris::Figure::rotate()
{
	rotationState = (rotationState + 1) % figureCoords.size();

	update();
}

//Якщо переміщення фігури в заданому напрямку призведе до колізій
//повертає false, в іншому випадку повертає true
bool Tetris::Figure::canMove(Vector2f direction, Cube*** cells)
{
	for (int i = 0; i < blocks.size(); i++) {
		Vector2f pos = blocks[i]->getPosition();

		//Приведення координат на ігровому полі до координат в масиві клітинок
		pos.x = pos.x / (BLOCK_SIZE + SPACING);
		pos.y = pos.y / (BLOCK_SIZE + SPACING);

		pos.x += direction.x;
		pos.y += direction.y;
		//координати потрібно округлити в більшу сторону
		if (cells[(int)(pos.x + 0.5f)][(int)(pos.y + 0.5f)] != nullptr) return false;
	}

	return true;
}

//Якщо при повороті фігури створюються колізії, метод повертає 
//false, в іншому випадку true
bool Tetris::Figure::canRotate(Cube*** cells)
{

	int rotationToCheck = (rotationState + 1) % figureCoords.size();

	for (int i = 0; i < figureCoords[rotationToCheck].size(); i++) {
		int x = figureCoords[rotationToCheck][i].x + xOffset;
		int y = figureCoords[rotationToCheck][i].y + yOffset;

		if (x <= 0 || x >= FIELD_WIDTH - 1 || y <= 0 || y >= FIELD_HEIGHT - 1) return false;
		if (cells[(int)(x + 0.5f)][(int)(y + 0.5f)] != nullptr) return false;
	}

	return true;
}

std::vector<Tetris::Cube*> Tetris::Figure::getAllCubes()
{
	return blocks;
}

void Tetris::Figure::move(int x, int y)
{
	xOffset += x;
	yOffset += y;

	update();
}

//Приватний метод, викликається лише в даному класі, якщо позиція
//була змінена
void Tetris::Figure::update()
{
	for (int i = 0; i < figureCoords[rotationState].size(); i++) {
		int x = figureCoords[rotationState][i].x + xOffset;
		int y = figureCoords[rotationState][i].y + yOffset;

		blocks[i]->setPosition(x * BLOCK_SIZE + x * SPACING, y * BLOCK_SIZE + SPACING * y);
	}
}

void Tetris::Figure::draw()
{
	for (Cube* c : blocks) {
		c->draw();
	}
}
