#include "Score.h"
#include "AIE.h"
#include <sstream>

Score::Score()
{
	m_scoreBar = CreateSprite("./images/Scorebar.png", 640, 40, false);
	m_healthSprite = CreateSprite("./images/health.png", 20, 20, false); //68 * 73 original sprite size

	m_score = 0;

	MoveSprite(m_scoreBar, 0, 40);
}

void Score::Draw(int* health)
{
	DrawSprite(m_scoreBar);

	switch (*health)
	{
	case 1:
		MoveSprite(m_healthSprite, 550, 30);
		DrawSprite(m_healthSprite);

		break;

	case 2:
		MoveSprite(m_healthSprite, 550, 30);
		DrawSprite(m_healthSprite);

		MoveSprite(m_healthSprite, 580, 30);
		DrawSprite(m_healthSprite);

		break;

	case 3:
		MoveSprite(m_healthSprite, 550, 30);
		DrawSprite(m_healthSprite);

		MoveSprite(m_healthSprite, 580, 30);
		DrawSprite(m_healthSprite);

		MoveSprite(m_healthSprite, 610, 30);
		DrawSprite(m_healthSprite);

		break;

	default:
		break;
	}

	DrawString("LIVES:", 440, 35);

	DrawString("SCORE:", 10, 35);
	std::stringstream score;
	score << m_score;
	DrawString(score.str().c_str(), 130, 35);
}

void Score::Update(int score)
{
	m_score += score;
}

int Score::GetScore()
{
	return m_score;
}

void Score::Reset()
{
	m_score = 0;
}