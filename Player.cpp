#include "Player.h"

#include "World.h"
extern World world;

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(string configFile)
{
	configFile = "config\\" + configFile;
	fstream stream;
	string tmp;
	stream.open(configFile);

	stream >> tmp >> m_playerImg;
	stream >> tmp >> m_objRect.w >> m_objRect.h;

	stream.close();
	numberOfFrames = 7;
	m_objRect.w /= numberOfFrames;
	m_imgRect.w = numberOfFrames * m_objRect.w;
	m_imgRect.h = m_objRect.h;


	m_playerImg = PLAYER_FOLDER + m_playerImg;
	m_objTexture = LoadTexture(m_playerImg, world.m_main_renderer);
	timer = time(NULL);

}

void Player::setInitialCoordinates(int x, int y)
{
	m_objRect.x = x;
	m_objRect.y = y;
}
void Player::setInitialMapCoordinates(int i, int j)
{
	m_map_coor.i = i;
	m_map_coor.j = j;
}

bool Player::isOnTile(int i, int j)
{
	if (m_map_coor.i == i && m_map_coor.j == j) return true;
	return false;
}

void Player::update()
{

}

void Player::draw()
{
	if ((time(NULL) - timer) % 1 == 0)
	{
		SDL_Rect presentRect;
		presentRect.w = m_objRect.w;
		presentRect.h = m_objRect.h;
		presentRect.x = frameCounter * presentRect.w;
		presentRect.y = 0;


		m_objRect.x += 50;
		m_objRect.y -= m_objRect.h / 2;

		SDL_RenderCopy(world.m_main_renderer, m_objTexture, &presentRect, &m_objRect);
		if (frameCounter == numberOfFrames - 1) frameCounter = 0;
		else
			frameCounter++;

		SDL_Delay(50);

		m_objRect.x -= 50;
		m_objRect.y += m_objRect.h / 2;
	}
}

void Player::moveTo(int x, int y)
{
	
	if (x - m_objRect.x > 0)
	{
		m_objRect.x += 8;
	}
	if (y - m_objRect.y > 0)
	{
		m_objRect.x -= (double)((world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.w * 1/2 )/ world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.h) * 6;
		m_objRect.y += 6;
	}

}

