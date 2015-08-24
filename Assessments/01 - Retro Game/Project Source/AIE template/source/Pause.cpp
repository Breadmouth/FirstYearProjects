#include "Pause.h"
#include "ScreenManager.h"
#include "AIE.h"


Pause::Pause(unsigned int width, unsigned int height, ScreenManager* sm)
	:Screen(width, height, sm)
{
	m_btn1 = CreateSprite("./images/btn1.png",180, 100, false);
	m_btn2 = CreateSprite("./images/btn2.png",180, 100, false);

	currentSelection = PLAY;
}

Pause::~Pause()
{

}

void Pause::Reset()
{
	currentSelection = PLAY;
}

void Pause::Update(float deltaTime)
{
	switch (currentSelection)
	{
	case PLAY:
		if (IsKeyDown(KEY_RIGHT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = QUIT;
			m_sm->ResetSelectionCooldown();
		}
		if (IsKeyDown(KEY_DOWN) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = SAVE;
			m_sm->ResetSelectionCooldown();
		}
		if(IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->ReturnToPrevious();
			m_sm->ResetSelectionCooldown();
		}
		break;

	case QUIT:
		if (IsKeyDown(KEY_LEFT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = PLAY;
			m_sm->ResetSelectionCooldown();
		}
		if (IsKeyDown(KEY_DOWN) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LOAD;
			m_sm->ResetSelectionCooldown();
		}
		if(IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->ResetScreen();
			m_sm->ReturnToPrevious();
			m_sm->ResetScreen();
			m_sm->SetScreen(7);
			m_sm->ResetSelectionCooldown();
		}
		break;

	case LOAD:
		if (IsKeyDown(KEY_LEFT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = SAVE;
			m_sm->ResetSelectionCooldown();
		}
		if (IsKeyDown(KEY_UP) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = QUIT;
			m_sm->ResetSelectionCooldown();
		}
		if(IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->Load();
		}
		break;

	case SAVE:
		if (IsKeyDown(KEY_RIGHT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LOAD;
			m_sm->ResetSelectionCooldown();
		}
		if (IsKeyDown(KEY_UP) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = PLAY;
			m_sm->ResetSelectionCooldown();
		}
		if(IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->Save();
		}
		break;

	default:
		break;
	}
}

void Pause::Draw(float deltaTime)
{
	switch (currentSelection)
	{
	case PLAY:
		MoveSprite(m_btn2, 120, 500);
		DrawSprite(m_btn2);
		
		DrawString("RESUME", 150, 465);

		MoveSprite(m_btn1, 120, 350);
		DrawSprite(m_btn1);
		
		DrawString("SAVE", 150, 315);

		MoveSprite(m_btn1, 360, 350);
		DrawSprite(m_btn1);
		
		DrawString("LOAD", 400, 315);

		MoveSprite(m_btn1, 360, 500);
		DrawSprite(m_btn1);

		DrawString("MENU", 400, 465);
		break;

	case QUIT:
		MoveSprite(m_btn1, 120, 500);
		DrawSprite(m_btn1);
		
		DrawString("RESUME", 150, 465);

		MoveSprite(m_btn1, 120, 350);
		DrawSprite(m_btn1);
		
		DrawString("SAVE", 150, 315);

		MoveSprite(m_btn1, 360, 350);
		DrawSprite(m_btn1);
		
		DrawString("LOAD", 400, 315);

		MoveSprite(m_btn2, 360, 500);
		DrawSprite(m_btn2);

		DrawString("MENU", 400, 465);
		break;

	case LOAD:
		MoveSprite(m_btn1, 120, 500);
		DrawSprite(m_btn1);
		
		DrawString("RESUME", 150, 465);

		MoveSprite(m_btn1, 120, 350);
		DrawSprite(m_btn1);
		
		DrawString("SAVE", 150, 315);

		MoveSprite(m_btn2, 360, 350);
		DrawSprite(m_btn2);
		
		DrawString("LOAD", 400, 315);

		MoveSprite(m_btn1, 360, 500);
		DrawSprite(m_btn1);

		DrawString("MENU", 400, 465);
		break;

	case SAVE:
		MoveSprite(m_btn1, 120, 500);
		DrawSprite(m_btn1);
		
		DrawString("RESUME", 150, 465);

		MoveSprite(m_btn2, 120, 350);
		DrawSprite(m_btn2);
		
		DrawString("SAVE", 150, 315);

		MoveSprite(m_btn1, 360, 350);
		DrawSprite(m_btn1);
		
		DrawString("LOAD", 400, 315);

		MoveSprite(m_btn1, 360, 500);
		DrawSprite(m_btn1);

		DrawString("MENU", 400, 465);
		break;

	default:
		break;
	}
}