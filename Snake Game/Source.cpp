#include"Game.h"
int main() {
	bool* Dead;
	Rock* rock;
	std::list<SnakeSegment>* snake;
	std::list<Food>* Foods;
	int* Foodx;
	int* FoodY;
	int* Score;
	int* SnakeDirection;

	bool* LeftKey{}, RightKey{}, OldLeft{}, OldRight = false;

	//Screen Buffer
	wchar_t *screen = new wchar_t[Area];
	HANDLE hConsle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsle);
	DWORD dwBytesWritten = 0;

	while (true) 
	{
		bool Dead = false;
		std::list<SnakeSegment> snake = {  {  60,15 } ,{61,15}};
		std::list<Food> Foods = { {30,15},{30,20} };
		Rock rock = { 70,18 };
		int Foodx = 30;
		int FoodY = 15;
		int Score = 0;
		int SnakeDirection = 3;

		bool LeftKey{}, RightKey{}, OldLeft{}, OldRight = false;


		
		while (!Dead)
		{

			
			Movement(&SnakeDirection,&RightKey,&LeftKey,&OldRight,&OldLeft,&snake);

			Collision_Detection(screen,&Dead,&Score,&snake,&Foods,&rock);
			UpdateScreen(screen,&Dead,  &Score, &snake,&Foods ,&rock);

			WriteConsoleOutputCharacter(hConsle, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

		}

 		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
		


	}
	


	return 0;
}