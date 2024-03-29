#pragma once
#include "IResource.h"
#include "ITransformable.h"
#include "Camera.h"
#include <glad.h>
#include "Vector.h"
#include "VAO.h"
#include "Texture.h"
#include "Shader.h"
#include <string>
#include <vector>

class Model : public IResource, public Transform
{
	struct Vertex;

public:
	Model();
	~Model();

	void virtual Initialize(const std::string& fileName)override;
	void OpenGlSetup()override;
	void SetVAO();

	void Draw(Texture& textures, Shader& shader, Camera& p_camera);

	void Delete()override;

	const float SCALE = 0.5f; // TODO : remove scale in SetModel

protected:
	bool SetModel(const std::string& p_fileName);

	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	VAO m_vao;
	//LibMath::Matrix4 m_projViewModelMat;

	const std::string ModelPath = "../assets/meshes/";

	void InterpretFace(	std::istringstream& p_line,
						const std::vector<LibMath::Vector3>& allPos,
						const std::vector<LibMath::Vector3>& allNor,
						const std::vector<LibMath::Vector2>& allUv,
						const LibMath::Vector3& offset);

	struct Vertex
	{
		LibMath::Vector3 m_pos;
		LibMath::Vector3 m_nor;
		LibMath::Vector2 m_uv;
	};
};

