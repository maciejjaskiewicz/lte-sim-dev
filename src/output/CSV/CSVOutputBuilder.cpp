#include "CSVOutputBuilder.h"

CSVOutputBuilder::CSVOutputBuilder(const std::string& fileName, int saveBatchSize) 
	: m_SaveBatchSize(saveBatchSize)
{
	m_File.open(fileName, std::ofstream::out | std::ofstream::trunc);
	LTE_SIM_ASSERT(m_File.is_open());

	m_File << OutputModel::GetCSVHeader() << std::endl;
}

CSVOutputBuilder::~CSVOutputBuilder()
{
	Close();
}

void CSVOutputBuilder::Add(std::unique_ptr<OutputModel> outputModel)
{
	m_OutputBuffer.push_back(std::move(outputModel));

	if(m_OutputBuffer.size() >= m_SaveBatchSize)
	{
		WriteBufferToFile();
		m_OutputBuffer.clear();
	}
}

void CSVOutputBuilder::Close()
{
	if(!m_OutputBuffer.empty())
	{
		WriteBufferToFile();
		m_OutputBuffer.clear();
	}

	m_File.close();
}

void CSVOutputBuilder::WriteBufferToFile()
{
	for (auto& outputModel : m_OutputBuffer)
	{
		m_File << outputModel->ToString(CSV) << std::endl;
	}
}
