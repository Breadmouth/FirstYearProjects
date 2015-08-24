#include "Time.h"
#include "GLFW/glfw3.h"

float Time::prevTime = 0;
float Time::deltaTime = 0;

void Time::Update()		//update must be called once a frame
{
	float currTime = (float)glfwGetTime();
	deltaTime = currTime - prevTime;
	prevTime = currTime;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}