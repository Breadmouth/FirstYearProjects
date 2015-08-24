#include "LevelSelect.h"
#include "ScreenManager.h"
#include "AIE.h"

LevelSelect::LevelSelect(unsigned int width, unsigned int height, ScreenManager* sm)
	:Screen(width, height, sm)
{
	m_space = CreateSprite("./images/space.png", 640, 800, false);
	m_title = CreateSprite("./images/LevelSelect.png", 640, 200, false);
	m_level1 = CreateSprite("./images/Level1.png",200,200,false);
	m_level2 = CreateSprite("./images/Level2.png",200,200,false);
	m_level3 = CreateSprite("./images/Level3.png",200,200,false);
	m_pointer = CreateSprite("./images/Pointer.png",50,50,false);

	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;

	currentSelection = LEVEL1;
}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::Reset()
{
	m_space1Y = 800.0f;
	m_space2Y = 1599.0f;

	currentSelection = LEVEL1;
}

void LevelSelect::Update(float deltaTime)
{
	m_space1Y -= (150 * deltaTime);
	m_space2Y -= (150 * deltaTime);

	if (IsKeyDown(KEY_ESCAPE))
	{
		m_sm->SetScreen(1);
	}

	switch (currentSelection)
	{
	case LEVEL1:
		if (IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->SetScreen(0);
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_RIGHT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LEVEL2;
			m_sm->ResetSelectionCooldown();
		}
		break;

	case LEVEL2:
		if (IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->SetScreen(4);
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_RIGHT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LEVEL3;
			m_sm->ResetSelectionCooldown();
		}
		if (IsKeyDown(KEY_LEFT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LEVEL1;
			m_sm->ResetSelectionCooldown();
		}
		break;

	case LEVEL3:
		if (IsKeyDown(KEY_ENTER) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			m_sm->SetScreen(5);
			m_sm->ResetSelectionCooldown();
		}

		if (IsKeyDown(KEY_LEFT) && m_sm->GetSelectionCooldown() < 0.0f)
		{
			currentSelection = LEVEL2;
			m_sm->ResetSelectionCooldown();
		}
		break;

	default:
		break;
	}
}

void LevelSelect::Draw(float deltaTime)
{
	ClearScreen();

	MoveSprite(m_space, 0, m_space1Y);
	DrawSprite(m_space);

	MoveSprite(m_space, 0, m_space2Y);
	DrawSprite(m_space);

	if (m_space1Y <= 0)
	{
		m_space1Y = 800.0f;
		m_space2Y = 1599.0f;
	}

	MoveSprite(m_title, 0, 700);
	DrawSprite(m_title);

	MoveSprite(m_level1, 10, 400);
	DrawSprite(m_level1);
	DrawString("Level 1", 60, 200);

	MoveSprite(m_level2, 220, 400);
	DrawSprite(m_level2);
	DrawString("Level 2", 270, 200);

	MoveSprite(m_level3, 430, 400);
	DrawSprite(m_level3);
	DrawString("Level 3", 480, 200);

	switch (currentSelection)
	{
		case LEVEL1:
			MoveSprite(m_pointer, 85, 450);
			DrawSprite(m_pointer);
			break;

		case LEVEL2:
			MoveSprite(m_pointer, 295, 450);
			DrawSprite(m_pointer);
			break;

		case LEVEL3:
			MoveSprite(m_pointer, 505, 450);
			DrawSprite(m_pointer);
			break;

		default:
			break;

	}
}