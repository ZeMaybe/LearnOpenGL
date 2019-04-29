
#ifndef Mesh_h__
#define Mesh_h__

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GLCommon/OpenGLShaderLoader.h"

namespace GLCommon
{
	struct Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec2 m_texCoords;
		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;
	};

	struct Texture 
	{
		unsigned int m_id;
		std::string m_type;
		std::string m_path;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();

		void Draw(Shader shader); 

	public:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;
		unsigned int m_vao = 0;

	private:
		void SetupMesh();
		void ClearUp();

		unsigned int m_vbo = 0;
		unsigned int m_ebo = 0;
	};

	/*
	class Mesh {
public:
	


private:

};
	*/


};

#endif // Mesh_h__