
#ifndef Model_h__
#define Model_h__

#include "GLCommon/Mesh.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include <assimp/material.h>

#include <vector>
#include <string> 

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace GLCommon
{
	class Model
	{
	public:
		Model(std::string const &path, bool gamma = false);
		~Model();

		void Draw(Shader shader);

	public:
		std::vector<Mesh> m_meshes;
		bool m_gammaCorrection = false;
		std::string m_directory;
		std::vector<Texture> m_texturesLoaded;

	private:
		void LoadModel(std::string const & path);

		void ProcessNode(aiNode *node, const aiScene *scene);
		Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	};
};

#endif // Model_h__