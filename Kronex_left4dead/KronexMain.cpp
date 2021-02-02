#include "KronexMain.h"

bool WINAPI DllMain(HINSTANCE hInstanceDLL, DWORD dwCallReason, LPVOID lpvReserved)
{
	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstanceDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)C_CheatMgr::main, hInstanceDLL, NULL, NULL);
    
		return true;
	}
	else if (dwCallReason == DLL_PROCESS_DETACH)
	{
		return true;
	}
	return false;
}
