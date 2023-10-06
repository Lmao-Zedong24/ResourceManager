#include "IGameManager.h"


OpenGl::IGameManager::IGameManager()
{
	this->CurrentState = OpenGl::GameState::INIT;
}

OpenGl::IGameManager::~IGameManager()
{
}

void OpenGl::IGameManager::Init()
{
}

void OpenGl::IGameManager::Update()
{
}

void OpenGl::IGameManager::ReadConfigFile(const std::string& p_fileName)
{
}

OpenGl::Renderer& OpenGl::IGameManager::GetRenderer()
{
	return this->Renderer;
}
