#include "Renderer.h"

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

OpenGl::Renderer::Renderer()
{
}

OpenGl::Renderer::~Renderer()
{
}

void OpenGl::Renderer::Init()
{

}

void OpenGl::Renderer::Quit()
{
}

void OpenGl::Renderer::Render()
{
    //BeginDrawing();
    //{
    //    ClearBackground(DARKGREEN);
    //    DrawSprites();
    //}
    //EndDrawing();

}
/*
OpenGl::Sprite* OpenGl::Renderer::CreateSprite(const std::string& fileName, Vector2 Position, Layer zLayer)
{
    if (sprites.size() <= zLayer)
        sprites.resize(zLayer + 1);

    Sprite* newSprite = new Sprite(*this->GetTexture(fileName), Position, zLayer);

    sprites[zLayer].push_back(newSprite);

    return sprites[zLayer].back();
}

void OpenGl::Renderer::RemoveSprite(OpenGl::Sprite* s)
{
    sprites[s->Layer].remove(s);
}

void OpenGl::Renderer::LoadTextureFile(const std::string& fileName)
{
    //auto it = (name.end() - 7); //gets ###.png
    //std::string key = "";
    //key += *(it);
    //key += *(++it);
    //key += *(++it);  //keeps the 3 numbers

    this->textures[fileName] = LoadTexture((this->Path + fileName).c_str());
}

const Texture2D* OpenGl::Renderer::GetTexture(const std::string& fileName)
{
    if (textures.count(fileName) == 0) //texture not loaded
    {
        LoadTextureFile(fileName);
    }
    return &(textures.at(fileName));
}

void OpenGl::Renderer::DrawSprites()const
{
    int it1 = 0;
    for (auto& list: this->sprites)
    {
        int it2 = 0;
        for (auto& sprite : list)
        {
            auto a = *sprite->Texture;
            auto b = sprite->Position;

            DrawTexture(*sprite->Texture, static_cast<int>(sprite->Position.x), static_cast<int>(sprite->Position.y), WHITE);

            it2++;
        }
        it1++;
    }
}

*/
