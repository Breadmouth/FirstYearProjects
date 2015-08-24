/**
*	@author	Iain Dowling
*	@brief	This file provides the constructor and functions unique to the ScreenManager class	
*			this class controls which screens are to be displayed and handles updating them
**/

#pragma once

class Level1;
class Level2;
class Level3;
class HighScore;
class Screen;
class Menu;
class LevelSelect;
class SplashScreen;
class Pause;

class ScreenManager
{
private:
	Level1* m_level1;
	Level2* m_level2;
	Level3* m_level3;
	HighScore* m_highScore;
	Menu* m_menu;
	Screen* m_activeScreen;
	Screen* m_previousScreen;
	LevelSelect* m_levelSelect;
	SplashScreen* m_splashScreen;
	Pause* m_pause;

	int currentScreen;

	bool m_quit;

	float m_selectionCooldown;
	float m_selectionResetTime;

	int width;
	int height;

public:
	ScreenManager();
	~ScreenManager();

	//calls update on everything it manages
	void Update(float deltaTime);

	//calls draw on everything it manages
	void Draw(float deltaTime) const;

	//the game loop to be called from main
	void Run();

	//changes the active screen
	void SetScreen(int screen);

	//return to the previous active screen
	void ReturnToPrevious();

	//resets the current active screen
	void ResetScreen();

	//saves progress in a level to save.txt
	void Save();

	//loads level progress
	void Load();

	//returns the time until the next selection can be made
	//used mainly in level select and menu
	float GetSelectionCooldown() const;

	//resets time until next selection can be made
	void ResetSelectionCooldown();

	void QuitGame();

};