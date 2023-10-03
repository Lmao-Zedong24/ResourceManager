#include "IResource.h"
#include <string>
#include <fstream>
#include <filesystem>


//namespace Multi
//{
//	std::string IResource::FileToString(const std::string& fileName, const std::string& p_resourcePath)
//	{
//		std::ifstream file;
//		file.open(p_resourcePath + fileName);
//
//		if (!file.is_open())
//			return std::string();
//
//		std::ostringstream sstr;
//		sstr << file.rdbuf();
//
//		return sstr.str();
//	}
//}