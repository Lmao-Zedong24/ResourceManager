#pragma once
#include <string>

namespace Multi
{
	class IResource
	{
	public:
		virtual bool Initialize(const std::string& fileName) {};
		virtual void Delete() {};

	protected:
		std::string FileToString(const std::string& fileName, const std::string& p_resourcePath = "");
	};

}

