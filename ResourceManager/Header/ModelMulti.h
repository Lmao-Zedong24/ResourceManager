#pragma once
#include "IResource.h"
#include "ITransformable.h"
#include "Model.h"
#include <string>
#include <vector>
#include <map>

namespace Multi
{
	class ModelMulti : public Model
	{
	public: 
		void setThreadPollId(int id);
		void Initialize(const std::string& fileName)override;

	private:
		struct VertexThreadInfo
		{
			bool											isReading = false;
			int												size = 0;
			int												finished = 0;
			std::map<int, std::vector<LibMath::Vector3>>	allPos, 
															allNor;
			std::map<int, std::vector<LibMath::Vector2>>	allUv;
			std::vector<std::istringstream>					faces;

			bool isFinished() 
			{ 
				return !isReading && size == finished; 
			};
		};

		void fileReader(const std::string& fileName);
		void startInterpret(std::string&& subFile, std::shared_ptr<VertexThreadInfo> vertInfo, int index);
		void stringInterpreter(std::shared_ptr<std::string> subString, std::shared_ptr<VertexThreadInfo> ptr, int index);
		void assembleFacesVerteciesIndicies(std::shared_ptr<VertexThreadInfo> vertInfo);
		template<typename T>
		void moveVector2dto1d(std::map<int, std::vector<T>>& from, std::vector<T>& to);

		const int	MAX_SUBFILE_STRING_LEN = 10000;
		int			m_pollId = 0;
		std::mutex	mutex;

	};
}
