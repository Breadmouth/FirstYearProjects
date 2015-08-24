#include "SplashScreen.h"
#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Sprite.h"

SplashScreen::SplashScreen(Game* game) : GameState(game->GetGameStateManager()), m_game(game)
{
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::Update(float deltaTime)
{
	m_bg->Update(deltaTime);
	m_countDown -= deltaTime;

	if (m_countDown < 0)
	{
		m_gsm->Pop();
		m_gsm->PushState("game");
	}
}

void SplashScreen::Draw(float deltaTime)
{
	m_bg->Draw(deltaTime);
}

void SplashScreen::Init()
{
	m_bg = new Sprite(m_game, "Splash.png", 800, 600);
	m_countDown = 2.0f;
}

void SplashScreen::Deinit()
{
	delete m_bg;
}