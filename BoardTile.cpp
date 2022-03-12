#include "BoardTile.h"
using namespace std;

#include "World.h"
extern World world;

BoardTile::BoardTile()
{
	init("board_tile.txt");
	isHighlighted = false;
}

BoardTile::~BoardTile()
{
}

void BoardTile::init(string configFile)
{
	configFile = "config\\" + configFile;

	ifstream stream;
	string tmp;
	stream.open(configFile);

	stream >> tmp >> m_tileImg;
	stream >> tmp >> m_objRect.w >> m_objRect.h;

	stream.close();
	m_tileImg = TILES_FOLDER + m_tileImg;
	m_objTexture = LoadTexture(m_tileImg, world.m_main_renderer);
	hasAQBoard = false;

	m_objRect.w -= 20;
	m_objRect.h -= 20;
}

void BoardTile::update()
{
	if (m_myQBoard != NULL) hasAQBoard = true;
}

void BoardTile::draw()
{
	/*if (isHighlighted)
	{
		D(m_objRect.x);
		D(m_objRect.y);
		D(m_objRect.w);
		D(m_objRect.h);
		SDL_Rect presentRect;
		
		presentRect.w = m_objRect.w;
		presentRect.h = m_objRect.h*3;

		presentRect.x = 0 + presentRect.w * currFrame;
		presentRect.y = 0;
		D(presentRect.x);
		D(presentRect.y);
		D(presentRect.w);
		D(presentRect.h);

		SDL_RenderCopy(world.m_main_renderer, m_objTexture, &presentRect, &m_objRect);
		SDL_Delay(40);
		if (currFrame < 2)
		{
			currFrame++;
		}
		else
		{
			currFrame = 0;
		}
		
	}
	else
	{*/
		SDL_RenderCopyEx(world.m_main_renderer, m_objTexture, NULL, &m_objRect, NULL, NULL, SDL_FLIP_VERTICAL);
	//}

}

void BoardTile::highlight()
{
	isHighlighted = true;
	m_objTexture = LoadTexture("tiles\\MathGame_Tile_Highlight1.bmp", world.m_main_renderer);
	//m_objRect.w *= 3;
}

void BoardTile::fall()
{
	m_objRect.y += 10;
}
