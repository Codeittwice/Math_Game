#pragma once

#include <windows.h>
#include <fstream>
#include <iostream>
#include<SDL.h>
#include "Engine.h"
#include <vector>
#include "BoardTile.h"
#include "Player.h"
#include "QBoard.h"
using namespace std;


class GameBoard
{
private:
	int m_boardCap;
public:
	GameBoard();
	~GameBoard();

	string m_boardImg;
	SDL_Rect m_objRect;
	SDL_Texture* m_objTexture;

	BoardTile* m_currentTile;
	vector<vector<BoardTile*>> m_tileMap;
	vector<BoardTile*> newPath;
	int p = 0;
	int frameCounter = 0;

	Player* player;
	vector<QBoard*> m_qBoards;

	void init(string configFile);
	void update();
	void draw();

	void initSession();
	void deleteSession();

	vector<BoardTile*> createPath();
	void addPlayer();
	void movePlayer();
};

