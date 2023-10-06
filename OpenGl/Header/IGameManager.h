#pragma once
#include "Renderer.h"
#include "Shader.h"

namespace OpenGl
{
	enum class GameState
	{
		INIT,
		MAIN_MENU,
		RUNNING,
		GAME_OVER,
		QUIT,
		ERROR
	};

	class IGameManager
	{
	public:
		IGameManager();
		~IGameManager();

		virtual void Init();
		virtual void Update();
		virtual void ReadConfigFile(const std::string& p_fileName);

		//TODO : put shader in renderer
		virtual void TempFunc(Shader&) {} ;

		OpenGl::Renderer& GetRenderer();

	protected:

		OpenGl::Renderer Renderer;
		OpenGl::GameState CurrentState;
	};
}

