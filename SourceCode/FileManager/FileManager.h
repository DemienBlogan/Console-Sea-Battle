#pragma once
#include <string>

class FileManager
{
public:
	static std::wstring ReadTextFile(const std::wstring& fileName);
};