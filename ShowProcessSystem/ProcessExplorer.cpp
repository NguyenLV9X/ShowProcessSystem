#include "ProcessExplorer.h"

bool ProcessExplorer::set_processes()
{
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
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

void ProcessExplorer::show_processes()
{
	for (auto it = mapProcesses.begin(); it != mapProcesses.end(); )
	{
		if (mapProcesses.count(it->second.th32ParentProcessID) == 0 || it->second.th32ParentProcessID == 0 && it->first != 0)
		{
			std::cout << "|-";
			std::wstring a1(it->second.szExeFile);
			std::string str(a1.begin(), a1.end());
			std::cout << " " << str << std::endl;
			show_child(it->first, 1);
			mapProcesses.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void ProcessExplorer::show_child(DWORD ID, int level)
{
	for ( auto it = mapProcesses.begin(); it != mapProcesses.end(); )
	{
		if (it->second.th32ParentProcessID == ID)
		{
			std::cout << "|-";
			std::wstring a1(it->second.szExeFile);
			std::string str(a1.begin(), a1.end());
			for (int i = 0; i < level; i++)
				std::cout << "-|-";
			std::cout << " " << str << std::endl;
			show_child(it->first, level + 1);
			mapProcesses.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void ProcessExplorer::start()
{
	if (!set_processes())
		return;

	show_processes();
}

ProcessExplorer::ProcessExplorer()
{
}

ProcessExplorer::~ProcessExplorer()
{
}
