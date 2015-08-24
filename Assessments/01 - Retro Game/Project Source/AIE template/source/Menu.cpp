#include "Menu.h"
#include "ScreenManager.h"
#include "AIE.h"

Menu::Menu(unsigned int width, unsigned int height, ScreenManager* sm)
	:Screen(width, height, sm)
{
	m_space = CreateSprite("./images/space.png", 640, 800, false);
	m_title = CreateSprite("./images/title.png", 640, 200, false);
	m_btn1 = CreateSprite("./images/btn1.png",180, 100, false);
	m_btn2 = CreateSprite("./images/btn2.png",180, 100, false);

	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;

	currentSelection = PLAY;
}

Menu::~Menu()
{

}

void Menu::Reset()
{
	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;

	currentSelection = PLAY;
}

void Menu::Update(float deltaTime)
{
	


	/*		following code updates the menu based on user input		*/
	switch (currentSelection)
	{
	case PLAY:

		if (IsKeyDown(KEY_ENTER))
		{
			m_sm->SetScreen(2);
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_DOWN) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = SCORES;
			m_sm->ResetSelectionCooldown();
		}

		break;

	case SCORES:

		if (IsKeyDown(KEY_DOWN) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = QUIT;
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_UP) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = PLAY;
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->SetScreen(7);
			m_sm->ResetSelectionCooldown();
		}

		break;

	case QUIT:

		if (IsKeyDown(KEY_UP) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = SCORES;
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_ENTER))
		{
			m_sm->QuitGame();
			m_sm->ResetSelectionCooldown();
		}

		break;

	default:
		break;
	}


	//updates the scrolling background
	m_space1Y -= (150 * deltaTime);
	m_space2Y -= (150 * deltaTime);
}

void Menu::Draw(float deltaTime)
{
	SetBackgroundColour (SColour( 7, 9, 27, 156));
	ClearScreen();
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


	// draws the title
	MoveSprite(m_title, 0, 700);
	DrawSprite(m_title);


	/*		following code draws the buttons		*/
	MoveSprite(m_btn1, 230, 480);
	DrawSprite(m_btn1);
	DrawString("PLAY", 290, 445);
		
	MoveSprite(m_btn1, 230, 360);
	DrawSprite(m_btn1);
	DrawString("SCORES", 260, 325);
	
	MoveSprite(m_btn1, 230, 240);
	DrawSprite(m_btn1);
	DrawString("QUIT", 290, 205);

	switch (currentSelection)
	{
	case PLAY:
		MoveSprite(m_btn2, 230, 480);
		DrawSprite(m_btn2);
		DrawString("PLAY", 290, 445);

		break;

	case SCORES:
		MoveSprite(m_btn2, 230, 360);
		DrawSprite(m_btn2);
		DrawString("SCORES", 260, 325);

		break;

	case QUIT:
		MoveSprite(m_btn2, 230, 240);
		DrawSprite(m_btn2);
		DrawString("QUIT", 290, 205);
		break;

	default:
		break;
	}
}