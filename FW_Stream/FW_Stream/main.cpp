#include <string.h>
#include <iostream>
#include "FW_Stream.h"

using namespace std;

//Variable
int exitF;
FW_Stream m_stream;

//Main
int main()
{
	if (m_stream.FW_open("option.ini"))
	{
		int value1 = atoi(m_stream.FW_search("Value").c_str());
		cout << value1 << endl;
		int value2 = atoi(m_stream.FW_search("Value2").c_str());
		cout << value2 << endl;
		cout << value1 + value2 << endl;
	}
	m_stream.FW_close();

	cin >> exitF;
	return 0;
}