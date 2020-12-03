/////////////////////////////INCLUDE/////////////////////////
#include "FW_Stream.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
** class FW_Stream
*/

FW_Stream::FW_Stream()
{}

FW_Stream::~FW_Stream()
{
	if(m_file)
		FW_close();
}

bool FW_Stream::FW_open(string filePos)
{
	m_file.open(filePos.c_str());
	if(m_file)
		return true;
	else
		return false;
}

bool FW_Stream::FW_close()
{
	if(m_file)
	{
		m_file.close();
		return true;
	}
	else
		return false;
}

string FW_Stream::FW_search(string optionSearch)
{
	m_file.seekg(0, std::ios::beg);
	string result, loopEnd;

	do
	{
		string line, contentSub, parameterName, value;

		getline(m_file, line);
		contentSub = line.substr(0, 1);
		if (contentSub != "")
		{
			if (contentSub != "[")
			{ 
				size_t separatorPos = line.find("=");
				for (size_t loop(0); loop < line.length(); loop++)
				{
					contentSub = line[loop];
					
					if (loop < separatorPos)
						parameterName += contentSub;

					if (loop > separatorPos)
						value += contentSub;
				}

				loopEnd = parameterName;
				result = value;
			}
		}
	} while (loopEnd != optionSearch && !m_file.eof());

	return result;
}

bool FW_Stream::FW_write(string optionName, string value)
{
	return false;
}