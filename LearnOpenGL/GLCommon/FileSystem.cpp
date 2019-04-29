
#include "GLCommon/FileSystem.h"
#include <shlobj.h>

using namespace GLCommon;

OpenGLFileSystem::OpenGLFileSystem()
{

}

OpenGLFileSystem::~OpenGLFileSystem()
{

}

std::string OpenGLFileSystem::GetLogFolder()
{
	char buffer[MAX_PATH];

	HRESULT hr = SHGetFolderPath(0,
		CSIDL_LOCAL_APPDATA,
		0,
		SHGFP_TYPE_CURRENT,
		buffer
	);

	std::string result = buffer;

	return(result);
}

std::string OpenGLFileSystem::GetDataFolder()
{
	return sDataFolder;
}
std::string OpenGLFileSystem::GetModelsFolder()
{
	return sDataFolder + sModelsSubFolder;
}
std::string OpenGLFileSystem::GetShaderFolder()
{
	return sDataFolder + sShaderSubFolder;
}
std::string OpenGLFileSystem::GetTextureFolder()
{
	return sDataFolder + sTextureSubFolder;
}

void OpenGLFileSystem::SetDataFolder(const std::string& folder)
{
	sDataFolder = folder;
}
void OpenGLFileSystem::SetModelsFolder(const std::string& folder)
{
	sModelsSubFolder = folder;
}
void OpenGLFileSystem::SetShaderFolder(const std::string& folder)
{
	sShaderSubFolder = folder;
}
void OpenGLFileSystem::SetTextureFolder(const std::string& folder)
{
	sTextureSubFolder = folder;
}

bool OpenGLFileSystem::FileExists(const std::string& file)
{
	DWORD dwAttrib = GetFileAttributes(file.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
bool OpenGLFileSystem::FileIsNewer(const std::string& file1, const std::string& file2)
{
	// This method assumes that the existance of the files has already been verified!

	HANDLE handle1 = INVALID_HANDLE_VALUE;
	HANDLE handle2 = INVALID_HANDLE_VALUE;

	handle1 = CreateFile(file1.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	handle2 = CreateFile(file2.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	FILETIME fileTime1;
	FILETIME fileTime2;

	// Get the file's time info
	GetFileTime(handle1, nullptr, nullptr, &fileTime1);
	GetFileTime(handle2, nullptr, nullptr, &fileTime2);

	// Close the files
	CloseHandle(handle1);
	CloseHandle(handle2);

	// Return the comparison
	if (fileTime1.dwHighDateTime > fileTime2.dwHighDateTime) {
		return(true);
	}
	else if (fileTime1.dwHighDateTime == fileTime2.dwHighDateTime) {
		return(fileTime1.dwLowDateTime > fileTime2.dwLowDateTime);
	}

	return(false);
}

std::string OpenGLFileSystem::sDataFolder = "../Data/";
std::string OpenGLFileSystem::sModelsSubFolder = "Models/";
std::string OpenGLFileSystem::sShaderSubFolder = "Shaders/";
std::string OpenGLFileSystem::sTextureSubFolder = "Textures/";