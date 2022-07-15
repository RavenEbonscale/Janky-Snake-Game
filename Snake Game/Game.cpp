#include "Game.h"
/// <summary>
/// Changes the Direction of The Snake
/// 
/// </summary>
/// <param name="SnakeDirection">Where the Snake is Heading</param>
/// <param name="RightKey"></param>
/// <param name="LeftKey"></param>
/// <param name="OldRight"></param>
/// <param name="OldLeft"></param>
/// <param name="snake"></param>
void Movement(int* SnakeDirection, bool* RightKey, bool* LeftKey, bool* OldRight, bool* OldLeft, std::list<SnakeSegment>* snake)
{
	auto t1 = std::chrono::system_clock::now();
	while ((std::chrono::system_clock::now() - t1) < ((*SnakeDirection % 2 == 1) ? std::chrono::milliseconds(120) : std::chrono::milliseconds(200))) {
		*RightKey = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
		*LeftKey = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

		if (*RightKey && !*OldRight)
		{
			(* SnakeDirection)++;
			if (*SnakeDirection == 4) *SnakeDirection = 0;
		}

		if (*LeftKey && !*OldLeft)
		{
		(*SnakeDirection)--;
			if (*SnakeDirection == -1) *SnakeDirection = 3;
		}

		*OldRight = *RightKey;
		*OldLeft = *LeftKey;
	}
	switch (*SnakeDirection)
	{
	case 0:
		
		snake->push_front({ snake->front().x, snake->front().y - 1 });
		break;
	case 1:
		snake->push_front({ snake->front().x + 1, snake->front().y });
		break;
	case 2:
		snake->push_front({ snake->front().x, snake->front().y + 1 });
		break;
	case 3:
		snake->push_front({ snake->front().x - 1, snake->front().y });
		break;
	}
	snake->pop_back();
}


/// <summary>
/// Logic For when you hit a wall/Food/Rock
/// </summary>
/// <param name="screen"></param>
/// <param name="Dead"></param>
/// <param name="Score"></param>
/// <param name="snake"></param>
/// <param name="Foods"></param>
/// <param name="rock"></param>
void Collision_Detection(wchar_t* screen, bool* Dead, int* Score, std::list<SnakeSegment>* snake,std::list<Food>* Foods,Rock* rock)
{


#pragma region Hit an Obstical 




	if (snake->front().x < 0 || snake->front().x >= nScreenWidth) {
		*Dead = true;
	}

	if (snake->front().y < 3 || snake->front().y >= nScreenHeight)
		*Dead = true;
	if (snake->front().x == rock->x && snake->front().y == rock->y)
		*Dead = true;
#pragma endregion

#pragma region Ate?



	for (std::list<Food>::iterator food = Foods->begin(); food != Foods->end(); food++)
	{

		if (snake->front().x == food->x && snake->front().y == food->y)
		{
			(*Score)++;
			while (screen[food->y * nScreenWidth + food->x] != L' ')
			{
				food->x = rand() % nScreenWidth;
				food->y = (rand() % (nScreenHeight - 3)) + 3;
				
				rock->x = rand() % nScreenWidth;
				rock->y = (rand() % (nScreenHeight - 3)) + 3;
				

			}
			for (int i = 0; i < 2; i++) {

				snake->push_back({ snake->back().x,snake->back().y });
			}





		}

}
#pragma endregion


#pragma region Hit Self?

	for (std::list<SnakeSegment>::iterator i = snake->begin(); i != snake->end(); i++)
	{
		if (i != snake->begin() && i->x == snake->front().x && i->y == snake->front().y) {
			*Dead = true;
		}
	}
#pragma endregion

}


/// <summary>
/// All the Visual Stuff ^>^
/// </summary>
/// <param name="Screen">Where else would you play?</param>
/// <param name="Dead">Is the player dead?</param>
/// <param name="Score">How Good are they?</param>
/// <param name="snake">slither slither</param>
/// <param name="Foods">Where the food is</param>
/// <param name="rock">Where the obstical is</param>
void UpdateScreen(wchar_t* screen, bool* Dead, int* Score, std::list<SnakeSegment>* snake ,std::list<Food>* Foods,Rock* rock)
{


	for (int i = 0; i < Area; i++) screen[i] = L' ';
	for (int i = 0; i < nScreenWidth; i++) {
		screen[i] = L'=';
		screen[2 * nScreenWidth + i] = L'=';
	}
	wsprintf(&screen[nScreenWidth + 5], L"Raven Ebonscales Snake Game Thing                Score: %d", *Score);
	for (auto s : *snake) { screen[s.y * nScreenWidth + s.x] = *Dead ? L'+' : L'*'; }

	screen[snake->front().y * nScreenWidth + snake->front().x] = *Dead ? L'!' : L'@';
	for (std::list<Food>::iterator food = Foods->begin(); food != Foods->end(); food++)
	{
		screen[food->y * nScreenWidth + food->x] = L'F';
	}
	screen[rock->y * nScreenWidth + rock->x] = L'R';

	if (*Dead) {
		wsprintf(&screen[15 * nScreenWidth + 40], L" Press 'Space' To Plag Again");
	}

}

void StartGame()
{
}
