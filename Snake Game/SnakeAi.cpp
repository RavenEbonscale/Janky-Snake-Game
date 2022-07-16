#include "SnakeAi.hpp"

SnakeAi::SnakeAi()
{
}

void SnakeAi::BestMove(SnakeSegment* snake,std::list<Food> *foods, int* Actions)
{
	float PossibleMoves[2][4];
	int fsize = foods->size();
	for (int i = 0; i < fsize; i++) {
		std::list<Food>::iterator food = foods->begin();
		std::advance(food,i);
			PossibleMoves[i][0] = SnakeAi::Distnace(snake->x, snake->y - 1, food->x, food->y);
			PossibleMoves[i][1] = SnakeAi::Distnace(snake->x + 1, snake->y, food->x, food->y);
			PossibleMoves[i][2] = SnakeAi::Distnace(snake->x, snake->y + 1, food->x, food->y);
			PossibleMoves[i][3] = SnakeAi::Distnace(snake->x - 1, snake->y, food->x, food->y);
		}
	


	float distance = 1000000;
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 4; y++) {
			if (PossibleMoves[x][y] <= distance) {
				distance = PossibleMoves[x][y];
				*Actions = y;
			}
		}
	}



}

float SnakeAi::Distnace(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
