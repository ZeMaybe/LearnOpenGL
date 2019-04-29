
#include "GLCommon/Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace GLCommon;
using namespace std;

Model::Model(string const &path, bool gamma = false)
	:m_gammaCorrection(gamma)
{
	LoadModel(path);
}

Model::~Model()
{

}

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].Draw(shader);
}


void Model::LoadModel(string const & path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// 遍历并复制顶点数据
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 tmp;

		// position
		tmp.x = mesh->mVertices[i].x;
		tmp.y = mesh->mVertices[i].y;
		tmp.z = mesh->mVertices[i].z;
		vertex.m_position = tmp;

		// normals 
		tmp.x = mesh->mNormals[i].x;
		tmp.y = mesh->mNormals[i].y;
		tmp.z = mesh->mNormals[i].z;
		vertex.m_normal = tmp;



	}



}

/*


Mesh processMesh(aiMesh *mesh, const aiScene *scene)
{
// Walk through each of the mesh's vertices
for (unsigned int i = 0; i < mesh->mNumVertices; i++)
{
// texture coordinates
if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
{
glm::vec2 vec;
// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
vec.x = mesh->mTextureCoords[0][i].x;
vec.y = mesh->mTextureCoords[0][i].y;
vertex.TexCoords = vec;
}
else
vertex.TexCoords = glm::vec2(0.0f, 0.0f);

// tangent
vector.x = mesh->mTangents[i].x;
vector.y = mesh->mTangents[i].y;
vector.z = mesh->mTangents[i].z;
vertex.Tangent = vector;
// bitangent
vector.x = mesh->mBitangents[i].x;
vector.y = mesh->mBitangents[i].y;
vector.z = mesh->mBitangents[i].z;
vertex.Bitangent = vector;
vertices.push_back(vertex);
}
// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
for (unsigned int i = 0; i < mesh->mNumFaces; i++)
{
aiFace face = mesh->mFaces[i];
// retrieve all indices of the face and store them in the indices vector
for (unsigned int j = 0; j < face.mNumIndices; j++)
indices.push_back(face.mIndices[j]);
}
// process materials
aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
// Same applies to other texture as the following list summarizes:
// diffuse: texture_diffuseN
// specular: texture_specularN
// normal: texture_normalN

// 1. diffuse maps
vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
// 2. specular maps
vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
// 3. normal maps
std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
// 4. height maps
std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

// return a mesh object created from the extracted mesh data
return Mesh(vertices, indices, textures);
}
*/