#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::Draw(float deltaTime)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); itr++)
	{
		(*itr)->Draw(deltaTime);
	}
}

void GameStateManager::Update(float deltaTime)
{
	//first we process all our commands
	ProcessCommands();

	//now we update all our states
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}
}

void GameStateManager::ProcessCommands()
{
	for (auto i = m_commands.begin(); i != m_commands.end(); ++i)
	{
		if ((*i).Name == POP)
		{
			if (m_states.size() > 0)
			{
				m_states.pop_back();
			}
		}
		else if ((*i).Name == PUSH)
		{
			auto itr = m_stateNames.find((*i).Data);
			if (itr != m_stateNames.end())
			{
				m_states.push_back(itr->second);
			}
		}
	}
	m_commands.clear();
}

void GameStateManager::RegisterGameState(const char* name, GameState* state)
{
	m_stateNames[name] = state;
}

void GameStateManager::Pop()
{
	Command command;
	command.Name = POP;
	command.Data = nullptr;
	m_commands.push_back(command);
}

void GameStateManager::PushState(const char* name)
{
	Command command;
	command.Name = PUSH;
	command.Data = name;
	m_commands.push_back(command);
}
