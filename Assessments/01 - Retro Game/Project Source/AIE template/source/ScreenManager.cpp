#include "ScreenManager.h"
#include "Level1.h"
#include "level2.h"
#include "Level3.h"
#include "HighScore.h"
#include "LevelSelect.h"
#include "SplashScreen.h"
#include "Pause.h"
#include "Menu.h"
#include "AIE.h"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;


ScreenManager::ScreenManager()
{
	width = 640;
	height = 780;
	Initialise(width, height, false, "RAIDEN");


	m_level1 = new Level1(width, height, this);
	m_level2 = new Level2(width, height, this);
	m_level3 = new Level3(width, height, this);
	m_highScore = new HighScore(width, height, this);
	m_menu = new Menu(width, height, this);
	m_levelSelect = new LevelSelect(width, height, this);
	m_splashScreen = new SplashScreen(width, height, this);
	m_pause = new Pause(width, height, this);
	m_activeScreen = m_splashScreen;
	m_previousScreen = m_splashScreen;

	m_quit = false;

	m_selectionCooldown = 0.0f;
	m_selectionResetTime = 0.3f;

}

ScreenManager::~ScreenManager()
{
	delete m_menu;
	delete m_level1;
	delete m_level2;
	delete m_level3;
	delete m_levelSelect;
	delete m_splashScreen;
	delete m_pause;
	delete m_highScore;
	Shutdown();
}

void ScreenManager::Update(float deltaTime)
{
	m_activeScreen->Update(deltaTime);
}

void ScreenManager::Draw(float deltaTime) const
{
	m_activeScreen->Draw(deltaTime);
}

void ScreenManager::Run()
{
	do
	{
		float deltaTime = GetDeltaTime();
		m_selectionCooldown -= deltaTime;

		Update(deltaTime);
		Draw(deltaTime);
	} while (FrameworkUpdate() == false && m_quit == false);
}

void ScreenManager::SetScreen(int screen)
{
	switch (screen)
	{
	case 0:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_level1;
		currentScreen = 0;
		break;

	case 1:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_menu;
		break;

	case 2:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_levelSelect;
		break;

	case 3:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_menu;
		break;

	case 4:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_level2;
		currentScreen = 1;
		break;

	case 5:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_level3;
		currentScreen = 2;
		break;

	case 6:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_pause;
		break;

	case 7:
		m_previousScreen = m_activeScreen;
		m_activeScreen = m_highScore;

	default:
		break;
	}
}

void ScreenManager::ReturnToPrevious()
{
	Screen* temp;
	temp = m_activeScreen;
	m_activeScreen = m_previousScreen;
	m_previousScreen = temp;
}

void ScreenManager::ResetSelectionCooldown()
{
	m_selectionCooldown = m_selectionResetTime;
}

float ScreenManager::GetSelectionCooldown() const
{
	return m_selectionCooldown;
}

void ScreenManager::ResetScreen()
{
	m_activeScreen->Reset();
}

void ScreenManager::Save()
{
	ofstream saveFile;
	saveFile.open("save.txt", ios::out);
	if (saveFile.is_open())
	{
		//player, score, enemy vector, bullet vector, enemybullet vector, background needed for successful full save
		saveFile << currentScreen << endl;
		saveFile.close();
	}
}

void ScreenManager::Load()
{
	ifstream saveFile;
	string saveData;
	stringstream input;

	saveFile.open("save.txt", ios::in);
	if (saveFile.is_open())
	{
		getline (saveFile,saveData);
		input << saveData;
		input >> currentScreen;
		saveFile.close();

		if (currentScreen == 0)
		{
			m_activeScreen = m_level1;
		}
		else if (currentScreen == 1)
		{
			m_activeScreen = m_level2;
		}
		else
		{
			m_activeScreen = m_level3;
		}
	}
}

void ScreenManager::QuitGame()
{
	m_quit = true;
}