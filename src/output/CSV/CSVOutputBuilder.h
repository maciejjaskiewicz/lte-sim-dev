#ifndef CSVOUTPUTBUILDER_H
#define CSVOUTPUTBUILDER_H

#include "core/Core.h"
#include "output/Models/OutputModel.h"

#include <fstream>
#include <vector>

class LTE_SIM_API CSVOutputBuilder
{
public:
	CSVOutputBuilder(const std::string& fileName, int saveBatchSize = 1000);
	~CSVOutputBuilder();
	void Add(std::unique_ptr<OutputModel> outputModel);
	void Close();
private:
	std::ofstream m_File;
	int m_SaveBatchSize;
	std::vector<std::unique_ptr<OutputModel>> m_OutputBuffer;

	void WriteBufferToFile();
};

#endif