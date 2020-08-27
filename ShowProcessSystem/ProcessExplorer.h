#include <Windows.h>
#include <iostream>
#include <map>
#include <tlhelp32.h>
using namespace std;

class ProcessExplorer 
{
private:
	map<DWORD, PROCESSENTRY32> mapProcesses;
	bool set_processes();
	void show_processes();
	void show_child(DWORD ID, int level);
public:
	void start();
	ProcessExplorer();
	~ProcessExplorer();
};