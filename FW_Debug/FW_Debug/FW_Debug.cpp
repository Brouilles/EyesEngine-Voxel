/////////////////////////////INCLUDE/////////////////////////
#include "FW_Debug.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class FW_Debug
*/
FW_Debug::FW_Debug()
{ }

FW_Debug::~FW_Debug()
{ }

/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
void FW_Debug::FW_success(std::string text, FW_debugType type, FW_debugType type2 = FW_debugType::NOTHING)
{
	text = "[SUCCESS]" + text;
	FW_windowType windowType = FW_windowType::INFORMATION;
	FW_write(text, type, type2, windowType);
}

void FW_Debug::FW_warning(std::string text, FW_debugType type, FW_debugType type2 = FW_debugType::NOTHING)
{
	text = "[WARNING]" + text;
	FW_windowType windowType = FW_windowType::WARNING;
	FW_write(text, type, type2, windowType);
}

void FW_Debug::FW_error(std::string text, FW_debugType type, FW_debugType type2 = FW_debugType::NOTHING)
{
	text = "[ERROR]" + text;
	FW_windowType windowType = FW_windowType::FATALERROR;
	FW_write(text, type, type2, windowType);
	exit(EXIT_FAILURE);
}

void FW_Debug::FW_window(string text, FW_windowType type_icon)
{
	if (type_icon == FW_windowType::FATALERROR)
		MessageBox(NULL, text.c_str(), "ERROR", MB_ICONERROR);
	else if (type_icon == FW_windowType::WARNING)
		MessageBox(NULL, text.c_str(), "WARNING", MB_ICONWARNING);
	else if (type_icon == FW_windowType::INFORMATION)
		MessageBox(NULL, text.c_str(), "INFORMATION", MB_ICONINFORMATION);
}

bool FW_Debug::FW_logs_reset()
{
	ofstream logs("FW_Debug.log");
	if(logs)
	{
		return true;
	}
	return false;
}

bool FW_Debug::FW_logs_write(string text)
{
	ofstream logs("FW_Debug.log", ios::app);
	if (logs)
	{
		logs << text.c_str() << endl;
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////
///		PRIVATE
/////////////////////////////////////////////////////////////
void FW_Debug::FW_write(string text, FW_debugType type, FW_debugType type2 = FW_debugType::NOTHING, FW_windowType windowType = FW_windowType::INFORMATION)
{
	if (type == FW_debugType::WINDOW || type2 == FW_debugType::WINDOW)
		FW_window(text, windowType);

	if (type == FW_debugType::LOGS || type2 == FW_debugType::LOGS)
		FW_logs_write(text);
}