
#include "GLCommon/OpenGLTexture.h"
#include "GLCommon/stb_image.h"

OpenGLImageLoader::Texture2D::Texture2D()
{

}

OpenGLImageLoader::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture);
}

void OpenGLImageLoader::Texture2D::Load(const GLchar* imagePath)
{
	// 获取 ID
	glGenTextures(1, &m_texture);
	// 绑定 ID
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// 设置参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_textureWrapHorizontal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_textureWrapVertical);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureMagFilter);

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(imagePath, &m_width, &m_height, &m_channelsInFile, 0);
	if (data)
	{
		if (m_channelsInFile == 3)
		{
			// 创建
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		if (m_channelsInFile == 4)
		{
			// 创建
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		// 创建mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOAD FAILED!" << std::endl;
		return;
	}

	// 释放内存
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLImageLoader::Texture2D::SetParams(int wh, int wv, int minFilter, int magFilter)
{
	m_textureWrapHorizontal = wh;
	m_textureWrapVertical = wv;
	m_textureMinFilter = minFilter;
	m_textureMagFilter = magFilter;
}

OpenGLImageLoader::Texture2D::Texture2D(const GLchar* imagePath, int wh, int wv, int minFilter, int magFilter)
{
	SetParams(wh, wv, minFilter, magFilter);
	Load(imagePath);
}

OpenGLImageLoader::Texture2D::Texture2D(const GLchar* imagePath)
{
	Load(imagePath);
}
