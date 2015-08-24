#include "Game.h"
#include "GameStateManager.h"
#include <GL/glew.h>
#include <GL/wglew.h>
//GLEW must procede everything else
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

unsigned int Game::CreateShader(unsigned int shaderType, const char *shaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(shaderFile);
	//if that worked ok, load file line by line
	if(shaderStream.is_open())
	{
		std::string Line = "";
		while(std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();
	
	//create shader ID
	GLuint uiShader = glCreateShader(shaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(shaderType)
		{
			case GL_VERTEX_SHADER: 
				strShaderType = "vertex"; 
				break;
			case GL_FRAGMENT_SHADER: 
				strShaderType = "fragment"; 
				break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

unsigned int Game::CreateProgram(const char *vertexShader, const char *fragmentShader)
{
	std::vector<GLuint> shaderList;

	m_vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShader);
	m_fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);

	shaderList.push_back(m_vertexShader);
	shaderList.push_back(m_fragmentShader);

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv (uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

void Game::Init(unsigned int width, unsigned int height, const char* title)
{
		//initialise GLFW
		if (!glfwInit())
		{
			return;
		}

		m_screenWidth = width;
		m_screenHeight = height;

		//create the window
		m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, title, NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			return;
		}

		//makes the windows context current
		glfwMakeContextCurrent(m_window);

		//initialise glew
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			return;
		}

		//create shaders
		m_program = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");
}

void Game::Deinit()
{
	glDeleteProgram(m_program);
	glfwDestroyWindow(m_window);
}

Game::Game()
{
	m_gsm = new GameStateManager();
}
Game::~Game()
{
	delete m_gsm;
}

void Game::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		m_time.Update();
		m_deltaTime = m_time.GetDeltaTime();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//enable shaders
		glUseProgram(m_program);

		Update(m_deltaTime);
		Draw(m_deltaTime);

		//swap buffers
		glfwSwapBuffers(m_window);

		//poll for evens
		glfwPollEvents();
	}
	Deinit();
	glfwTerminate();
}

void Game::Update(float deltaTime)
{
	m_gsm->Update(deltaTime);
}

void Game::Draw(float deltaTime)
{
	m_gsm->Draw(deltaTime);
}