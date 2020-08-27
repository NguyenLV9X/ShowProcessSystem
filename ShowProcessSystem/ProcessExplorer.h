#include <Windows.h>
#include <iostream>
#include <map>
#include <tlhelp32.h>
using namespace std;

class ProcessExplorer 
{
private:
	map<DWORD, PROCESSENTRY32> mapProcesses;
public:
	bool set_processes();
	ProcessExplorer();
	~ProcessExplorer();
};