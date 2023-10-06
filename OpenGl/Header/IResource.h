#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <filesystem>

class IResource
{
public:
	virtual void Delete() {}
	virtual void Initialize(const std::string& fileName) {};
	virtual void OpenGlSetup() {};

protected:
	std::string FileToString(const std::string& p_fileName, const std::string& p_resourcePath = "");
	std::string m_fileName;
};

