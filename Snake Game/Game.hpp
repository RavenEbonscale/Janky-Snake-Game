#include<iostream>
#include<Windows.h>
#include<thread>
#include <list>
#include<chrono>
#include<random>

#define nScreenWidth 120
#define nScreenHeight 30

#define Area nScreenWidth*nScreenHeight


struct SnakeSegment
{
	int x;
	int y;
};

struct Food {
	int x;
	int y;
};

struct Rock {
	int x;
	int y;
};


void Movement(int* SnakeDirection, bool* RightKey, bool* LeftKey, bool* OldRight, bool* OldLeft, std::list<SnakeSegment>* snake);
void Collision_Detection(wchar_t* screen,bool* dead,int* Score,std::list<SnakeSegment>* snake, std::list<Food>* Foods,Rock* rock);
void UpdateScreen(wchar_t* screen, bool* dead, int* Score, std::list<SnakeSegment>* snake, std::list<Food>* Foods, Rock* rock);
void StartGame();