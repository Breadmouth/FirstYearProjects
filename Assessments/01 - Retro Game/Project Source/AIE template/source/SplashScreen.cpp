#include "SplashScreen.h"
#include "AIE.h"
#include "ScreenManager.h"

SplashScreen::SplashScreen(unsigned int width, unsigned int height, ScreenManager* sm)
	:Screen(width, height, sm)
{
	m_splash = CreateSprite("./images/SplashScreen.png",  width, height, false);

	m_splashCooldown = 4.0f;

}

void SplashScreen::Reset()
{
}

void SplashScreen::Update(float deltaTime)
{
	m_splashCooldown -= deltaTime;
	if (m_splashCooldown < 0.0f)
	{
		m_sm->SetScreen(1);
	}
}

void SplashScreen::Draw(float DeltaTime)
{
	SetBackgroundColour (SColour( 7, 9, 27, 156));
	ClearScreen();

	MoveSprite(m_splash, 0, 780);
	DrawSprite(m_splash);
}