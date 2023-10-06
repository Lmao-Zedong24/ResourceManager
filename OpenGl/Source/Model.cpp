#include "Model.h"
#include "Camera.h"
#include "Vector.h"
#include <fstream>
#include <sstream>
#include <string>
#include "VBO.h"
#include "EBO.h"
#include <functional>

Model::Model() : Transform(LibMath::Matrix4(1))
{
}

Model::~Model()
{
	m_vao.Delete();
}

void Model::Initialize(const std::string& fileName)
{
	SetModel(fileName);
}

void Model::OpenGlSetup()
{
	SetVAO();
}

void Model::InterpretFace(	std::istringstream& p_line,	
							const std::vector<LibMath::Vector3>& allPos,
							const std::vector<LibMath::Vector3>& allNor,
							const std::vector<LibMath::Vector2>& allUv,
							const LibMath::Vector3& offset)
{
	int v, t, n; //posIndex, uvIndex, normalIndex
	std::string strVertex;
	std::vector<int> triangleIndex;
	triangleIndex.reserve(3); //min 3

	while (p_line >> strVertex) //for each vertex in p_line
	{
		std::replace(strVertex.begin(), strVertex.end(), '/', ' ');

		std::istringstream issVertex(std::move(strVertex));
		issVertex >> v; issVertex >> t; issVertex >> n; //posIndex, uvIndex, normalIndex

		int vertexIndex = -1;

		for (int i = 0; i < m_vertices.size(); i++) //check if in array already
		{
			if ((m_vertices[i].m_pos == allPos[v + static_cast<size_t>(offset.m_x)]) &&
				(m_vertices[i].m_nor == allNor[n + static_cast<size_t>(offset.m_y)]) &&
				(m_vertices[i].m_pos == allUv[ t + static_cast<size_t>(offset.m_z)]))
			{
				vertexIndex = i;
				break;
			}
		}

		if (vertexIndex == -1) //if not in array add
		{
			m_vertices.push_back({	allPos[v + static_cast<size_t>(offset.m_x)],
									allNor[n + static_cast<size_t>(offset.m_y)],
									allUv[ t + static_cast<size_t>(offset.m_z)]});
			vertexIndex = static_cast<int>(m_vertices.size() - 1);
		}

		triangleIndex.push_back(vertexIndex); //add triangleIndex
		strVertex = "";
	}

	for (int i = 2; i < triangleIndex.size(); i++)
	{
		this->m_indices.emplace_back(triangleIndex[0]);
		this->m_indices.push_back(triangleIndex[(size_t)i - 1]);
		this->m_indices.push_back(triangleIndex[i]);
	}
}

bool Model::SetModel(const std::string& p_fileName)
{
	std::ifstream file;
	file.open(ModelPath + p_fileName);

	if (!file.is_open())
		return false;

	std::string line, charac; //charac at start of line
	float f1, f2, f3;
	LibMath::Vector3 indexObjOffset(-1.0f); // pos/uv/norIndex indexObjOffset for stack space

	std::vector<LibMath::Vector3> allPos, allNor;
	std::vector<LibMath::Vector2> allUv;

	while (std::getline(file, line))
	{
		std::istringstream issLine{ std::move(line) };
		issLine >> charac;

		if (charac == "f")
		{
			InterpretFace(issLine, allPos, allNor, allUv, indexObjOffset);
			continue;
		}

		issLine >> f1; issLine >> f2; issLine >> f3;
		if (charac == "v")
			allPos.push_back(LibMath::Vector3(f1 * SCALE, f2 * SCALE, f3 * SCALE));
		else if (charac == "vt")
			allUv.push_back(LibMath::Vector2(f1, f2));
		else if (charac == "vn")
			allNor.push_back(LibMath::Vector3(f1, f2, f3));
	}

	file.close();
	return true;
}

void Model::SetVAO()
{
	m_vao.Bind();

	VBO vbo((GLfloat*)(&m_vertices[0]), m_vertices.size() * sizeof(Vertex));
	EBO ebo((GLuint*)(&m_indices[0]), m_indices.size() * sizeof(GLuint));

	m_vao.LinkVBO(vbo, 0, 3, sizeof(Vertex), (void*)0);
	m_vao.LinkVBO(vbo, 1, 3, sizeof(Vertex), (void*)(3 * sizeof(float)));
	m_vao.LinkVBO(vbo, 2, 2, sizeof(Vertex), (void*)(6 * sizeof(float)));

	m_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Model::Delete()
{
	m_vao.Delete();
}

void Model::Draw(Texture& p_texture, Shader& p_shader, Camera& p_camera)
{
	p_shader.Activate();
	m_vao.Bind();
	p_texture.Bind();

	
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
	m_vao.Unbind();
}

