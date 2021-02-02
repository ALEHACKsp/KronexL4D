#include <windows.h>
#include "C_CheatManager.h"
#include <ctime>
#include <iostream>

BOOL WINAPI DllMain(HINSTANCE hInstanceDLL, DWORD dwCallReason, LPVOID lpvReserved)
{
	//static clock_t time = clock();
	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstanceDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)C_CheatManager::main, hInstanceDLL, NULL, NULL);

		return TRUE;
	}
	else if (dwCallReason == DLL_PROCESS_DETACH)
	{
		/*char str[128];
		sprintf(str, "start cmd.exe /k \"echo time since inject: %d ms\"\0", clock() - time);
		system(str);
		std::cout << str << std::endl;*/
    //FreeLibrary(hInstanceDLL);
		return TRUE;
	}
	return FALSE;
}
