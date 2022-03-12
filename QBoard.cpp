#include "QBoard.h"

#include "World.h"
extern World world;

QBoard::QBoard()
{
}
QBoard::QBoard(const QBoard* model)
{
	m_objRect = model->m_objRect;
	m_objTexture = model->m_objTexture;
	isAnswered = model->isAnswered;
	isActive = model->isActive;
	shouldAppear = model->shouldAppear;
	shouldDisappear = model->shouldDisappear;
	gotTheQuestionRight = model->gotTheQuestionRight;
}

QBoard::~QBoard()
{
}

void QBoard::init(string configFile)
{
	configFile = "config\\" + configFile;
	fstream stream;
	string tmp;
	stream.open(configFile);

	stream >> tmp >> m_qBoardrImg;
	stream >> tmp >> m_objRect.w >> m_objRect.h;
	stream >> tmp >> m_tryAgainImg;
	stream >> tmp >> m_tryAgainRect.w >> m_tryAgainRect.h;

	stream.close();


	//m_qBoardrImg = m_qBoardrImg;
	m_objTexture = LoadTexture(m_qBoardrImg, world.m_main_renderer);
	m_tryAgainTexture = LoadTexture(m_tryAgainImg, world.m_main_renderer);

	m_objRect.x = world.m_SCREEN_WIDTH / 2 - m_objRect.w  * 2 / 3;
	m_objRect.y = - m_objRect.h;// world.m_SCREEN_HEIGHT / 2 - m_objRect.h / 2;

	isAnswered = false;
	shouldAppear = false;
	shouldDisappear = false;
	gotTheQuestionRight = true; 
	errMsgShouldStay = false;

}

void QBoard::generateQuestion()
{
	switch (rand() % 4) 
	{
	case 0:
		if (world.m_gameManager.m_availableOperators.add) 
		{
			int a = rand() % 9 + 1;
			int b = rand() % 9 + 1;
			m_qa.answer = to_string(a + b);
			m_qa.question = to_string(a) + " + " + to_string(b) + " = ";
		}
		break;
	case 1:
		if (world.m_gameManager.m_availableOperators.subtract)
		{
			int a = rand() % 9 + 1;
			int b = rand() % 9 + 1;
			if (a > b) {
				m_qa.answer = to_string(a - b);
				m_qa.question = to_string(a) + " - " + to_string(b) + " = ";
			}
			else {
				m_qa.answer = to_string(b - a);
				m_qa.question = to_string(b) + " - " + to_string(a) + " = ";
			}
		}
		break;
	case 2:
		if (world.m_gameManager.m_availableOperators.multiply) 
		{
			int a = rand() % 9 + 1;
			int b = rand() % 9 + 1;
			m_qa.answer = to_string(a * b);
			m_qa.question = to_string(a) + " . " + to_string(b) + " = ";
		}
		break;
	case 3:
		if (world.m_gameManager.m_availableOperators.divide) 
		{
			int a = rand() % 9 + 1;
			int b = rand() % 9 + 1;
			m_qa.answer = to_string(a * b / b);
			m_qa.question = to_string(a * b) + " : " + to_string(b) + " = ";
		}
		break;
	}

	if (m_qa.question == "")
	{
		generateQuestion();
	}

}

void QBoard::answerQuestion()
{
	if (world.m_gameManager.m_inputManager.m_EnterIsPressed)
	{
		/*D("enter pressed");
		D(input);
		D(m_qa.answer);*/
		//world.m_gameManager.m_inputManager.stopTextInput();
		if (input == m_qa.answer)
		{
			gotTheQuestionRight = true;
			shouldDisappear = true;
			isAnswered = true;
			switch (rand() % 3)
			{
			case 0:
				world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Right_Answer_str);
				break;
			case 1:
				world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Right_Answer2_str);
				break;
			case 2:
				world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Right_Answer3_str);
				break;
			}
			world.m_gameManager.m_gameboard.player->m_state = HAPPY;
			world.m_gameManager.m_inputManager.stopTextInput();
			//world.m_gameManager.m_inputManager.resetText();
		}
		else
		{
			if (gotTheQuestionRight) {
				timerErr = time(NULL);
				world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Wrong_Answer_str);
				gotTheQuestionRight = false;
				world.m_gameManager.m_inputManager.stopTextInput();
				world.m_gameManager.m_gameboard.player->m_state = ANGRY;
			}
			//world.m_gameManager.m_inputManager.resetText();


		}

	}

}

void QBoard::update()
{
	if (isActive)
	{
		if (!world.m_gameManager.m_inputManager.m_textInputIsActive && canContinueAsking)
		{
			world.m_gameManager.m_inputManager.startTextInput();
			
		}
		input = world.m_gameManager.m_inputManager.getTextInput();

		answerQuestion();
		//D("UPDATE");
		if (shouldAppear)
		{
			//D("APP");
			if (m_objRect.y <= 0) appear();
			else shouldAppear = false;
		}
		if (shouldDisappear)
		{
			//D("DAPP");
			if (m_objRect.y >= -m_objRect.h) disappear();
			else shouldDisappear = false;
		}
		if (sizeChangeCounter % 10 < 5)
		{

			m_objRect.w += 4;
			m_objRect.h += 4;
			m_objRect.x -= 2;
			m_objRect.y -= 2;
		}
		else
		{

			m_objRect.w -= 4;
			m_objRect.h -= 4;
			m_objRect.x += 2;
			m_objRect.y += 2;
		}
		sizeChangeCounter++;
	}

}

void QBoard::draw()
{
	
	if (isActive)
	{
		SDL_RenderCopy(world.m_main_renderer, m_objTexture, NULL, &m_objRect);

		if (time(NULL) - timerErr <= 3)
		{
			errMsgShouldStay = true;
		}else{
			errMsgShouldStay = false;

			gotTheQuestionRight = true;
		}

		

		if (gotTheQuestionRight)
		{
			Vector2 v;
			v.x = m_objRect.x + m_objRect.w / 2 - 400;
			v.y = m_objRect.y + m_objRect.h / 2 - 300;
			int font = 200;
			write(m_qa.question, v, world.m_main_renderer, font);
			v.x += 3 * font;
			if (input != "")
			{
				write(input, v, world.m_main_renderer, font);

			}
		}
		else
		{
			if (errMsgShouldStay)
			{
				m_tryAgainRect.x = m_objRect.x + m_objRect.w / 2 - 400;
				m_tryAgainRect.y = m_objRect.y + m_objRect.h / 2 - 350;

				SDL_RenderCopy(world.m_main_renderer, m_tryAgainTexture, NULL, &m_tryAgainRect);
				//writeRed("Пробвай пак", v, world.m_main_renderer, font);
				//gotTheQuestionRight = false;
			}
		}
		
	}
}

void QBoard::appear()
{
	m_objRect.y += 30;
}

void QBoard::disappear()
{
	
	m_objRect.y -= 30;
}