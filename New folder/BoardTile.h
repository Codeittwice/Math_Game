#pragma once
#include <windows.h>
#include <fstream>
#include <iostream>
#include<SDL.h>
#include "Engine.h"
#include "QBoard.h"
using namespace std;


class BoardTile
{

public:
	BoardTile();
	~BoardTile();

	string m_tileImg;
	SDL_Rect m_objRect;
	SDL_Texture* m_objTexture;

	map_coordinates map_coor;

	bool isHighlighted;
	bool hasAQBoard;
	int currFrame = 0;

	QBoard* m_myQBoard;

	void init(string configFile);
	void update();
	void draw();

	void highlight();
	void fall();


};

