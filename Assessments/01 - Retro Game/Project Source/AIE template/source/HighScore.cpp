#include "HighScore.h"
#include "ScreenManager.h"
#include "AIE.h"
#include "sqlite3.h"

HighScore::HighScore(unsigned int width, unsigned int height, ScreenManager* sm)
	:Screen(width, height, sm)
{
	m_space = CreateSprite("./images/space.png", 640, 800, false);
	m_title = CreateSprite("./images/HighScores.png", 640, 200, false);

	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;

	LoadScores();
}

HighScore::~HighScore()
{

}

void HighScore::Reset()
{
	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;
}

void HighScore::Update(float deltaTime)
{
	//updates the scrolling background
	m_space1Y -= (150 * deltaTime);
	m_space2Y -= (150 * deltaTime);

	if (IsKeyDown(KEY_ESCAPE) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->SetScreen(1);
			m_sm->ResetSelectionCooldown();
		}

	if (IsKeyDown(KEY_F5))
	{
		LoadScores();
	}
}

void HighScore::Draw(float deltaTime)
{
	SetBackgroundColour (SColour( 7, 9, 27, 156));
	ClearScreen();

	DrawString("F5 to refresh scores", 200, 50);

	//draws the scrolling background
	MoveSprite(m_space, 0, m_space1Y);
	DrawSprite(m_space);

	MoveSprite(m_space, 0, m_space2Y);
	DrawSprite(m_space);

	if (m_space1Y <= 0)
	{
		m_space1Y = 800.0f;
		m_space2Y = 1599.0f;
	}

	//draws title
	MoveSprite(m_title, 0, 750);
	DrawSprite(m_title);

	//display scores
	for (int i = 0; i < m_highScores.size(); i++)
	{
		char buffer[32];
		sprintf (buffer, "%s : %i", m_highScores[i].name.c_str(), m_highScores[i].score);


		DrawString (buffer, 230, 600 - (i * 40) );
	}
}

void HighScore::LoadScores()
{
	m_highScores.clear();

	sqlite3 * dataBase = NULL;
	sqlite3_open("game_db", &dataBase);

	std::string query = "SELECT name, score FROM tbl_scores ORDER BY score DESC LIMIT 10";

	char *err = NULL;
	sqlite3_exec(dataBase, query.c_str(), sqlite_query_callback, this, &err);

	sqlite3_close(dataBase);
}

int HighScore::sqlite_query_callback(void *userdata, int numArgs, char **data, char **columnName)
{
	HighScore *pState = (HighScore *) userdata;
	HighScoreEntry entry;
	entry.name = data[0];
	entry.score = std::stoi(data[1]);

	pState->m_highScores.push_back(entry);

	char *name = data[0];
	unsigned int score = std::stoi( data[1]);

	return 0;

}