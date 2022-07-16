#pragma once
#include <array>
#include <chrono>
#include <random>
#include "Game.hpp"
#include"GLobal.hpp"

class SnakeAi
{


public:
	SnakeAi();
	void BestMove(SnakeSegment*snake,std::list<Food> *foods,int *Action);
	
private:
	float Distnace(int x1, int y1, int x2, int y2);




};
