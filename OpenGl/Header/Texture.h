#pragma once
#include "IResource.h"
#include <glad.h>
#include <GLFW/glfw3.h>


class Texture : public IResource
{
public:
	Texture();
	~Texture();

	void Initialize(const std::string& p_fileName) override;
	void ThreadUnsafeSetup() override;

	void Bind();
	void Unbind();
	void Delete()override;

	GLuint m_id;
private:
	bool SetTexture(const std::string& p_fileName);
	const std::string TexturePath = "../assets/textures/";
};

