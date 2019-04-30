
#ifndef OpenGLTexture_h__
#define OpenGLTexture_h__

#include "GLCommon/OpenGLUtility.h"

namespace GLCommon
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
		static unsigned int Load(std::string imagePath,int* widht,int* height,int* channelsInFile);
		static unsigned int Load(const GLchar* imagePath, int* widht, int* height, int* channelsInFile);
		
		void Load(std::string imagePath);
		void Load(const GLchar* imagePath);
		void SetParams();
		void SetParams(int wh, int wv, int minFilter, int magFilter);

	private:
		unsigned int m_texture = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channelsInFile = 0;

		int m_textureWrapHorizontal = GL_REPEAT;
		int m_textureWrapVertical = GL_REPEAT;
		int m_textureMinFilter = GL_NEAREST;
		int m_textureMagFilter = GL_LINEAR;
	};
};

#endif // OpenGLTexture_h__