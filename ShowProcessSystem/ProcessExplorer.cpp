#include "ProcessExplorer.h"

bool ProcessExplorer::set_processes()
{
	PROCESSENTRY32 pe32;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return false;

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return false;
	}

	do
	{

		mapProcesses.insert ( pair<DWORD, PROCESSENTRY32>(pe32.th32ProcessID, pe32) );

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return true;
}

ProcessExplorer::ProcessExplorer()
{
}

ProcessExplorer::~ProcessExplorer()
{
}
