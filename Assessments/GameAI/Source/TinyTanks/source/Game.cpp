#include "Game.h"
#include "GameStateManager.h"
#include "Sprite.h"
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
	SetUpRenderToTexture();

	while (!glfwWindowShouldClose(m_window))
	{
		m_time.Update();
		m_deltaTime = m_time.GetDeltaTime();

		glBindFramebuffer(GL_FRAMEBUFFER, m_offscreenFB);
		glViewport(0,0,m_screenWidth,m_screenHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		//enable shaders
		glUseProgram(m_program);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Update(m_deltaTime);
		Draw(m_deltaTime);

		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,m_screenWidth,m_screenHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		m_sprite->Update(m_deltaTime);
		m_sprite->Draw(m_deltaTime);

		//swap buffers
		glfwSwapBuffers(m_window);

		//poll for events

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

void Game::SetUpRenderToTexture()
{
	m_sprite = new Sprite(this);

	//generate a framebuffer for our rendering
	glGenFramebuffers(1, &m_offscreenFB);
	glBindFramebuffer(GL_FRAMEBUFFER, m_offscreenFB);

	//the texture we're going to render to
	glGenTextures(1, &m_texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m_screenWidth, m_screenHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "m_texture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);

	// Set the list of draw buffers
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	
	//check for completeness of framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return;
	}

	//prepare our sprite
	m_sprite->SetTextureID(m_texture);
	m_sprite->SetAlpha(0.5f);
	m_sprite->SetHeight(m_screenHeight);
	m_sprite->SetWidth(m_screenWidth);
	m_sprite->SetPosition(0,0);
}