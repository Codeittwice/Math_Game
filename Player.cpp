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
	stream >> tmp >> m_playerImgIdle;
	stream >> tmp >> m_playerImgHappy;
	stream >> tmp >> m_playerImgAngry;
	stream >> tmp >> m_objRect.w >> m_objRect.h;

	D(m_playerImgIdle);
	D(m_playerImgHappy);
	D(m_playerImgAngry);

	stream.close();
	numberOfFrames = 7;
	m_objRect.w /= numberOfFrames;
	m_imgRect.w = numberOfFrames * m_objRect.w;
	m_imgRect.h = m_objRect.h;


	m_playerImg = PLAYER_FOLDER + m_playerImg;
	m_playerImgIdle = PLAYER_FOLDER + m_playerImgIdle;
	m_playerImgHappy = PLAYER_FOLDER + m_playerImgHappy;
	m_playerImgAngry = PLAYER_FOLDER + m_playerImgAngry;
	m_objTexture = LoadTexture(m_playerImg, world.m_main_renderer);
	m_objTextureIdle = LoadTexture(m_playerImgIdle, world.m_main_renderer);
	m_objTextureHappy = LoadTexture(m_playerImgHappy, world.m_main_renderer);
	m_objTextureAngry = LoadTexture(m_playerImgAngry, world.m_main_renderer);
	timer = time(NULL);

	m_state = IDLE;

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

		if (world.m_gameManager.m_gameState == GAME)
		{
			m_objRect.x += world.m_gameManager.m_gameboard.m_tileMap[0][0]->m_objRect.w / 2;
			m_objRect.y -= (m_objRect.h + world.m_gameManager.m_gameboard.m_tileMap[0][0]->m_objRect.h) / 2;
		}
		switch (m_state)
		{
		case 1:
			SDL_RenderCopy(world.m_main_renderer, m_objTextureIdle, &presentRect, &m_objRect);
			break;

		case 2:
			SDL_RenderCopy(world.m_main_renderer, m_objTexture, &presentRect, &m_objRect);
			break;

		case 3:
			SDL_RenderCopy(world.m_main_renderer, m_objTextureHappy, &presentRect, &m_objRect);
			break;

		case 4:
			SDL_RenderCopy(world.m_main_renderer, m_objTextureAngry, &presentRect, &m_objRect);
			break;
		}


		if (frameCounter == numberOfFrames - 1) frameCounter = 0;
		else
			frameCounter++;

		SDL_Delay(50);
		if (world.m_gameManager.m_gameState == GAME)
		{
			m_objRect.x -= world.m_gameManager.m_gameboard.m_tileMap[0][0]->m_objRect.w / 2;
			m_objRect.y += (m_objRect.h + world.m_gameManager.m_gameboard.m_tileMap[0][0]->m_objRect.h) / 2;
		}
	}
}

void Player::moveTo(int x, int y)
{
	
	if (x - m_objRect.x > 0)
	{
		m_objRect.x += 8;
	}
	if (x - m_objRect.x < 0)
	{
		m_objRect.x -= 8;
	}
	if (y - m_objRect.y > 0)
	{
		m_objRect.x += (double)((world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.w * 1/2 )/ world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.h) * 6;
		m_objRect.y += 6;
	}
	if (y - m_objRect.y < 0)
	{
		m_objRect.x -= (double)((world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.w * 1 / 2) / world.m_gameManager.m_gameboard.m_qBoards[0]->m_objRect.h) * 6;
		m_objRect.y -= 6;
	}

}

