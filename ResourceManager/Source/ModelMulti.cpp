#include "ModelMulti.h"
#include "ThreadPool.h"
#include <functional>
#include <sstream>

#include <concurrent_unordered_set.h>



namespace Multi 
{
	void ModelMulti::Initialize(const std::string& fileName)
	{
		std::function<void()> func = std::bind(&Multi::ModelMulti::fileReader, this, fileName);
		ThreadPoll::getInstance()->addFuncToThread(func);
	}

	void ModelMulti::fileReader(const std::string& fileName)
	{
		std::ifstream file;
		file.open (ModelPath + fileName);

		if (!file.is_open()) { return; }

		thread_local std::string line, subFile; //charac at start of line
		std::shared_ptr<VertexThreadInfo> vertInfo = std::make_shared<VertexThreadInfo>();

		vertInfo->isReading = true;
		vertInfo->size = 0;
		subFile.reserve(MAX_SUBFILE_STRING_LEN);

		int indexSplit = 0;
		while(std::getline(file, line))
		{
			if (subFile.size() + line.size() > MAX_SUBFILE_STRING_LEN)
				startInterpret(std::move(subFile), vertInfo, indexSplit++);

			subFile += line;
			subFile += '\n';
		}

		if (!subFile.empty())
			startInterpret(std::move(subFile), vertInfo, indexSplit++);

		{
			std::unique_lock lk(mutex);
			vertInfo->size = indexSplit;
			vertInfo->isReading = false;
		}

		file.close();
	}

	void ModelMulti::startInterpret(std::string&& subFile, std::shared_ptr<VertexThreadInfo> ptr, int index)
	{
		auto vertInfo = std::atomic_load(&ptr);

		std::function<void()> func = std::bind(&Multi::ModelMulti::stringInterpreter, this, std::make_shared<std::string>(subFile), vertInfo, index);
		Multi::ThreadPoll::getInstance()->addFuncToThread(func); //with subFile
		subFile = "";
	}

	void ModelMulti::stringInterpreter(std::shared_ptr<std::string> subString, std::shared_ptr<VertexThreadInfo> vertInfo, int index)
	{
		std::istringstream	stream{ std::move(*subString.get()) };
		std::string			line, charac; //charac at start of line
		float				f1, f2, f3;

		while (std::getline(stream, line))
		{
			std::istringstream issLine{std::move(line)};
			issLine >> charac;

			{
				std::unique_lock lk(mutex);

				if (charac == "f")
				{
					vertInfo->faces.emplace_back(std::move(issLine));
					continue;
				}
				issLine >> f1; issLine >> f2; issLine >> f3;

				if (charac == "v")
					vertInfo->allPos.insert({index, std::vector<LibMath::Vector3>()}).first->second.push_back(LibMath::Vector3(f1 * SCALE, f2 * SCALE, f3 * SCALE));
				else if (charac == "vt")
					vertInfo->allUv.insert({index, std::vector<LibMath::Vector2>()}).first->second.push_back(LibMath::Vector2(f1, f2));
				else if (charac == "vn")
					vertInfo->allNor.insert({index, std::vector<LibMath::Vector3>()}).first->second.push_back(LibMath::Vector3(f1, f2, f3));
			}

			charac = "";
			line = "";
		}

		bool callEndFunc = false;
		{
			std::unique_lock lk(mutex);
			vertInfo->finished++;

			callEndFunc = vertInfo->isFinished();
		}

		if (callEndFunc)
			assembleFacesVerteciesIndicies(vertInfo);
	}

	void ModelMulti::assembleFacesVerteciesIndicies(std::shared_ptr<VertexThreadInfo> vertInfo)
	{
		static LibMath::Vector3 indexObjOffset(-1.0f); // pos/uv/norIndex index .Obj file offset for stack space
		
		std::vector<LibMath::Vector3> poss;
		std::vector<LibMath::Vector3> nors;
		std::vector<LibMath::Vector2> uvs;

		{	//should be only popinter with access bcs called when finished
			std::unique_lock lk(mutex);
			moveVector2dto1d(vertInfo->allPos, poss);
			moveVector2dto1d(vertInfo->allNor, nors);
			moveVector2dto1d(vertInfo->allUv,  uvs);


			for (auto& line : vertInfo->faces)
				InterpretFace(line, poss, nors, uvs, indexObjOffset);
		}

		m_promise.set_value(dynamic_cast<IResource*>(this));
	}

	template<typename T>
	void ModelMulti::moveVector2dto1d(std::map<int, std::vector<T>>& from, std::vector<T>& to)
	{
		int totalsize = 0;
		for (int i = 0; i < from.size(); i++)
			totalsize += from[i].size();

		to.reserve(totalsize);
		for (int i = 0; i < from.size(); i++)
		{
			for (int j = 0; j < from[i].size(); j++)
				to.emplace_back(std::move(from[i][j]));
		}
	}

}


