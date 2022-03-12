#include "GameBoard.h"
using namespace std;

#include "World.h"
extern World world;

GameBoard::GameBoard()
{

}
GameBoard::~GameBoard()
{
}

void GameBoard::init(string configFile)
{
	configFile = "config\\" + configFile;

	fstream stream;
	string tmp;
	stream.open(configFile);

	stream >> tmp >> m_boardImg;
	stream >> tmp >> m_objRect.w >> m_objRect.h;
	stream >> tmp >> m_boardCap;
	stream >> tmp >> tmp;
	//m_objRect.w = world.m_SCREEN_WIDTH * 4;
	//m_objRect.h = world.m_SCREEN_HEIGHT;

	p = 0;
	stream.close();
	m_objTexture = LoadTexture(m_boardImg, world.m_main_renderer);
	m_overTexture = LoadTexture(tmp, world.m_main_renderer);

	player = new Player();
	player->init("player1.txt");
	
}


void GameBoard::update()
{
	if (p < newPath.size() - 1)
	{
		for (int i = 0; i < m_boardCap; i++)
		{
			for (int j = 0; j < m_boardCap; j++)
			{
				m_tileMap[i][j]->update();
			}
		}
		m_qBoards[p]->update();
		movePlayer();
	}
	else {

		player->moveTo(2000, newPath[newPath.size() - 1]->m_objRect.y - newPath[newPath.size() - 1]->m_objRect.h);
		player->m_state = MOVING;
		if (player->m_objRect.x >= 1920 && player->m_objRect.y >= 540)
		{
			world.m_gameManager.m_soundManager.stop(world.m_gameManager.m_soundManager.Background_Music_str);

			world.m_gameManager.m_gameState = ENDGAME;
		}
	}

	
	player->update();
}

void GameBoard::draw()
{
	
	if (p < newPath.size() - 1) 
	{
		for (int i = 0; i < m_boardCap; i++)
		{
			for (int j = 0; j < m_boardCap; j++)
			{
				m_tileMap[i][j]->draw();
			}
		}

		m_qBoards[p]->draw();
	}
	else {
		for (int i = 0; i < newPath.size(); i++)
		{
			newPath[i]->draw();
		}
	}

	SDL_RenderCopy(world.m_main_renderer, m_objTexture, NULL, NULL);

	player->draw();


	SDL_RenderCopy(world.m_main_renderer, m_overTexture, NULL, NULL);
}


void GameBoard::initSession()
{
	for (int i = 0; i < m_boardCap; i++)
	{
		vector<BoardTile*> row;
		for (int j = 0; j < m_boardCap; j++)
		{
			BoardTile* tile = new BoardTile();

			tile->m_objRect.x = 0 + (j * tile->m_objRect.w / 3) * 2 + (i * tile->m_objRect.w / 3);
			tile->m_objRect.y = 1080 - tile->m_objRect.h * m_boardCap + i * tile->m_objRect.h;


			tile->map_coor.i = i;
			tile->map_coor.j = j;

			row.push_back(tile);
		}
		m_tileMap.push_back(row);
	}
	m_objRect.w = 6 * m_tileMap[0][0]->m_objRect.w + 200;
	m_objRect.h = m_objRect.w * 10 / 28 + 200;
	m_objRect.x = m_tileMap[0][0]->m_objRect.x - m_objRect.w / 3 + 50;
	m_objRect.y = m_tileMap[0][0]->m_objRect.y - 20;

	newPath = createPath();
	m_currentTile = newPath[0];
	m_qBoards[0]->isActive = true;

	for (int p = 0; p < newPath.size(); p++)
	{
		for (int i = 0; i < m_boardCap; i++)
		{
			for (int j = 0; j < m_boardCap; j++)
			{
				if (newPath[p]->map_coor.i == i && newPath[p]->map_coor.j == j)
				{
					//m_tileMap[i][j]->highlight();
				}
			}
		}
	}
	m_qBoards[0]->shouldAppear = true;
	addPlayer();
	
	
}

void GameBoard::deleteSession()
{
	newPath.clear();
	m_qBoards.clear();
	m_tileMap.clear();
	p = 0;

}

vector<BoardTile*> GameBoard::createPath()
{
	vector<BoardTile*> path;
	int i = 0, j = 0;
	srand(time(NULL));
	while (i < m_boardCap - 2 && j < m_boardCap)
	{
		path.push_back(m_tileMap[i][j]);
		QBoard* qb = new QBoard(world.m_gameManager.m_configManager.m_qBoard);
		qb->generateQuestion();
		m_qBoards.push_back(qb);
		/*switch (rand() % 4)
		{
		case 0:
			if (i + 1 < m_boardCap)
			{
				i++;
				break;
			}
		case 1:
			if (j + 1 < m_boardCap)
			{
				j++;
				break;
			}
		case 2:
			if (j - 1 >= 0)
			{
				j--;
				break;
			}
		case 3:
			if (i - 1 >= 0)
			{
				i--;
				break;
			}
		}*/
		
		int r = rand() % 4;
		
		if (r <= 10)
		{
			
			if (i != m_boardCap - 3)
			{
				i++;
			}
			else {
				j++;
			}
		}
		else
		{
			if (j != m_boardCap - 1)
			{
				j++;
			}
			else {
				i++;
			}
		}

	}
	/*if (path.size() != 10)
	{
		path = createPath();

	}*/

	
	/*for (int i = 0; i < m_qBoards.size(); i++)
	{
		D(m_qBoards[i]->m_qa.question);
	}*/


	return path;


}

void GameBoard::addPlayer()
{
	player = new Player();
	player->init("player1.txt");

	player->setInitialMapCoordinates(m_tileMap[0][0]->map_coor.i, m_tileMap[0][0]->map_coor.i);
	player->setInitialCoordinates(m_tileMap[0][0]->m_objRect.x, m_tileMap[0][0]->m_objRect.y);

	newPath[p]->highlight();
}

void GameBoard::movePlayer()
{
	if (m_qBoards[p]->isAnswered == true)
	{
		//D("HERE");
		//m_qBoards[p]->shouldDisappear = true;
		if (!m_qBoards[p]->shouldDisappear)
		{
			if (player->m_objRect.x >= newPath[p + 1]->m_objRect.x
				&& player->m_objRect.y >= newPath[p + 1]->m_objRect.y)
			{
				if (p < newPath.size() - 1) {
					p++;
				}
				else {
					//p = 0;
					player->moveTo(540,1920);
				}
				for (int i = 0; i < m_qBoards.size(); i++)
				{
					m_qBoards[i]->isActive = false;
				}


				m_currentTile = newPath[p];
				m_qBoards[p]->isActive = true;
				m_qBoards[p]->shouldAppear = true;

				if (newPath[p]->m_myQBoard != NULL) newPath[p]->m_myQBoard->isAnswered = false;

				newPath[p]->highlight();

				player->m_state = IDLE;
			}
			else
			{
				player->moveTo(newPath[p + 1]->m_objRect.x, newPath[p + 1]->m_objRect.y);
				player->m_state = MOVING;
			}

		}
		//m_qBoards[p]->shouldDisappear = true;

	}
}
