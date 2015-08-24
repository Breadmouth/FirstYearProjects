#pragma once

#include <vector>
#include <map>

using namespace std;

class GameState;

class GameStateManager
{
protected:
	vector<GameState*> m_states;

	// creating a new inline enum to represent conmmands
	enum CommandName
	{
		POP,
		PUSH
	};

	// creating a new command struct to contain details about the command
	struct Command
	{
		CommandName Name;
		const char* Data;
	};

	vector<Command> m_commands;

	//go through all my commands and run them one by one
	void ProcessCommands();

	//a map ('dictionary') that associates GamesStates with a string representing their name
	map<const char*, GameState*> m_stateNames;

public:
	GameStateManager();
	virtual ~GameStateManager();

	void Update(float deltaTime);
	void Draw(float deltaTime);

	void Pop();
	void PushState(const char* stateName);

	//registers a new state with the GameStateManager using it's name
	//add new word to dictionary
	void RegisterGameState(const char* name, GameState* state);
};