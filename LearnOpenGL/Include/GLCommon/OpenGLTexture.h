
#ifndef OpenGLTexture_h__
#define OpenGLTexture_h__

#include "GLCommon/OpenGLUtility.h"

namespace OpenGLImageLoader
{

	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const GLchar* imagePath);
		Texture2D(const GLchar* imagePath,int wh,int wv,int minFilter,int magFilter);

		~Texture2D();
		
		unsigned int Texture()const { return m_texture; }

	public:
		void Load(const GLchar* imagePath);
		void SetParams(int wh, int wv, int minFilter, int magFilter);

	private:
		unsigned int m_texture = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channelsInFile = 0;

		int m_textureWrapHorizontal = GL_REPEAT;
		int m_textureWrapVertical = GL_REPEAT;
		int m_textureMinFilter = GL_LINEAR;
		int m_textureMagFilter = GL_LINEAR;
	};
};

/*

// texture 1
// ---------
glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load image, create texture and generate mipmaps
int width, height, nrChannels;
stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
if (data)
{
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
// texture 2
// ---------
glGenTextures(1, &texture2);
glBindTexture(GL_TEXTURE_2D, texture2);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load image, create texture and generate mipmaps
data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
if (data)
{
// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
*/

#endif // OpenGLTexture_h__