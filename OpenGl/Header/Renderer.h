#pragma once

#include <vector>
#include <list>
#include <map>
#include <string>


namespace OpenGl
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void Quit();
		void Render();

		//OpenGl::Sprite* CreateSprite(const std::string& str, Vector2 Position, OpenGl::Layer zLayer = 0);
		//void RemoveSprite(OpenGl::Sprite*);
		//const Texture2D* GetTexture(const std::string& name);
		
	private:
		//std::map<std::string, Texture2D> textures;
		//std::vector<std::list<OpenGl::Sprite*>> sprites;

		const std::string Path = "Assets/textures/PNG/Default size/";

		//void LoadTextureFile(const std::string& name);

	};
}

