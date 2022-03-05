#pragma once

#include <windows.h>
#include <fstream>
#include <iostream>
#include<SDL.h>
#include "Engine.h"
#include <vector>


class Player
{
public:
	Player();
	~Player();

	string m_playerImg;
	SDL_Rect m_objRect;
	SDL_Rect m_imgRect;
	SDL_Texture* m_objTexture;

	int numberOfFrames;
	int frameCounter = 0;

	time_t timer;

	Vector2 m_coor;
	map_coordinates m_map_coor;

	void init(string configFile);
	void setInitialCoordinates(int x, int y);
	void setInitialMapCoordinates(int i, int j);
	bool isOnTile(int i, int j);
	void update();
	void draw();
	void moveTo(int x, int y);
};

