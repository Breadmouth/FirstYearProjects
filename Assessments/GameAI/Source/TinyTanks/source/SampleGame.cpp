#include "SampleGame.h"
#include <GLFW/glfw3.h>
#include "Vec2.h"
#include "PlayingGameState.h"
#include "GameStateManager.h"
#include "SplashScreen.h"

SampleGame::SampleGame()
{

}

SampleGame::~SampleGame()
{

}

void SampleGame::Init()
{
	Game::Init(800, 600, "My Game!");

	m_splashScreen = new SplashScreen(this);
	m_splashScreen->Init();

	m_playingState = new PlayingGameState(this);
	m_playingState->Init();

	m_gsm->RegisterGameState("game", m_playingState);
	m_gsm->RegisterGameState("splash", m_splashScreen);
	m_gsm->PushState("splash");
}

void SampleGame::Deinit()
{
	delete m_playingState;
	Game::Deinit();
}

void SampleGame::Update(float deltaTime)
{
	Game::Update(deltaTime);
}

void SampleGame::Draw(float deltaTime)
{
	Game::Draw(deltaTime);
}
