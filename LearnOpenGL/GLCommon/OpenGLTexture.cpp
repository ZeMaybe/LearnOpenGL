
#include "GLCommon/OpenGLTexture.h"
#include "GLCommon/stb_image.h"

using namespace GLCommon;

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(const GLchar* imagePath, int wh, int wv, int minFilter, int magFilter)
{
	m_texture = Load(imagePath, &m_width, &m_height, &m_channelsInFile);
	SetParams(wh, wv, minFilter, magFilter);
}

Texture2D::Texture2D(const GLchar* imagePath)
{
	m_texture = Load(imagePath, &m_width, &m_height, &m_channelsInFile);
	SetParams();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture);
}

unsigned int Texture2D::Load(std::string imagePath, int* width, int* height, int* channelsInFile)
{
	return Load(imagePath.c_str(), width,height,channelsInFile);
}

unsigned int Texture2D::Load(const GLchar* imagePath, int* width, int* height, int* channelsInFile)
{
	unsigned int textureID; 
	glGenTextures(1, &textureID);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, width, height, channelsInFile, 0);
	if (data)
	{
		GLenum format;

		if (*channelsInFile == 1)
			format = GL_RED;
		else if (*channelsInFile == 3)
			format = GL_RGB;
		else if (*channelsInFile == 4)
			format = GL_RGBA;


		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, *width, *height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOAD FAILED!" << std::endl;
	}

	stbi_image_free(data);
	return textureID;
}


void Texture2D::Load(std::string imagePath)
{
	Load(imagePath.c_str());
}

void Texture2D::Load(const GLchar* imagePath)
{
	m_texture = Load(imagePath, &m_width, &m_height, &m_channelsInFile);
	SetParams();
}

void Texture2D::SetParams()
{
	SetParams(m_textureWrapHorizontal, m_textureWrapVertical, m_textureMinFilter, m_textureMagFilter);
}

void Texture2D::SetParams(int wh, int wv, int minFilter, int magFilter)
{
	m_textureWrapHorizontal = wh;
	m_textureWrapVertical = wv;
	m_textureMinFilter = minFilter;
	m_textureMagFilter = magFilter;

	if (m_texture != 0)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_textureWrapHorizontal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_textureWrapVertical);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureMinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureMagFilter);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

