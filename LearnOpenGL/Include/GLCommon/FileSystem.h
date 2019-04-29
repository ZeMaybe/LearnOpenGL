
#ifndef FileSystem_h__
#define FileSystem_h__

#include <string>

namespace GLCommon
{
	class OpenGLFileSystem
	{
	public:
		OpenGLFileSystem();
		~OpenGLFileSystem();

		std::string GetLogFolder();
		std::string GetDataFolder();
		std::string GetModelsFolder();
		std::string GetShaderFolder();
		std::string GetTextureFolder();

		void SetDataFolder(const std::string& folder);
		void SetModelsFolder(const std::string& folder);
		void SetShaderFolder(const std::string& folder);
		void SetTextureFolder(const std::string& folder);
		
		bool FileExists(const std::string& file);
		bool FileIsNewer(const std::string& file1, const std::string& file2);

	private:
		static std::string sDataFolder;
		static std::string sModelsSubFolder;
		static std::string sShaderSubFolder;
		static std::string sTextureSubFolder;
	};
};

#endif // FileSystem_h__