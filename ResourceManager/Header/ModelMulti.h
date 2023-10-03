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

namespace Multi
{
	class Model : public IResource, public Transform
	{
		struct Vertex;

	public:
		Model();
		~Model();

		void Initialize(const std::string& p_fileName) override;
		void Draw(Texture& textures, Shader& shader, Camera& p_camera);

		void Delete()override;
		void SetVAO();

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;
		VAO					m_vao;

		const std::string ModelPath = "../assets/meshes/";

		void InterpretFace(std::istringstream&	line,
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
}
