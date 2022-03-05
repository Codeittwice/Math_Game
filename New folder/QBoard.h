#pragma once

#include <windows.h>
#include <fstream>
#include <iostream>
#include<SDL.h>
#include "Engine.h"
#include <vector>

struct QA {
	string question;
	string answer;
};



class QBoard
{
public:
	QBoard();
	QBoard(const QBoard* model);
	~QBoard();

	string m_qBoardrImg;
	SDL_Rect m_objRect;
	SDL_Texture* m_objTexture;

	string m_tryAgainImg;
	SDL_Rect m_tryAgainRect;
	SDL_Texture* m_tryAgainTexture;


	bool isAnswered;
	bool isActive;
	int r;
	QA m_qa;

	string input;

	int sizeChangeCounter = 0;


	bool gotTheQuestionRight;
	bool canContinueAsking = true;
	bool shouldAppear;
	bool shouldDisappear;
	bool errMsgShouldStay;
	time_t timerErr;

	void init(string configFile);
	void generateQuestion();
	void answerQuestion();
	void update();
	void draw();

	void appear();
	void disappear();
};



