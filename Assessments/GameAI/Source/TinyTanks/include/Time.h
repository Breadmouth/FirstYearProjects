#pragma once

class Time
{
public:

	static void Update();
	static float GetDeltaTime();

private:

	static float prevTime;
	static float deltaTime;

};