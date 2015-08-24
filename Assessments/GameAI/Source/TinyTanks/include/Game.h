#pragma once

struct GLFWwindow;
class SimpleSprite;
class GameStateManager;
class Sprite;

#include "Time.h"

class Game
{
protected:
	GameStateManager* m_gsm;

	GLFWwindow* m_window;

	unsigned int m_screenHeight;
	unsigned int m_screenWidth;

	unsigned int m_program;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;

	unsigned int CreateShader(unsigned int shaderType, const char *shaderFile);
	unsigned int CreateProgram(const char *vertexShader, const char *fragmentShader);

	Time m_time;
	float m_deltaTime;

	unsigned int m_texture;
	unsigned int m_offscreenFB;
	Sprite* m_sprite;
	void SetUpRenderToTexture();

public:
	Game();
	virtual ~Game();
	void Init(unsigned int width, unsigned int height, const char* title);
	void Run();

	virtual void Deinit();

	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);

	inline unsigned int GetScreenHeight()	const
	{
		return m_screenHeight;
	}
	inline unsigned int GetScreenWidth()	const
	{
		return m_screenWidth;
	}
	inline GLFWwindow* GetWindow()	const
	{
		return m_window;
	}
	inline GameStateManager* GetGameStateManager()	const
	{
		return m_gsm;
	}
};