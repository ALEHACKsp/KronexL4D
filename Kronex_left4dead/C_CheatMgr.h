#pragma once

class C_CheatMgr
{
public:
	static DWORD main(HINSTANCE hInstanceDll);
  static C_Cheat* GetCheat(const string &cheatName);
  static void KronexCmdExecFn(IConVar* var, const char *pOldValue, float flOldValue);
  static void KronexCmdExecCvarFn(IConVar* var, const char *pOldValue, float flOldValue);

  template <typename T> T SearchInterface(CreateInterfaceFn factory, string name);

  void SendPacketStatus(bool bSendPacketStatus) const;

  static C_CheatMgr* Instance;

  HANDLE hCurProcess;
  HINSTANCE m_hInstanceDll;

	DWORD dwEngineDll;
  MODULEINFO miEngineDll;

	DWORD dwClientDll;
  MODULEINFO miClientDll;

	DWORD dwServerDll;
  MODULEINFO miServerDll;

  DWORD dwVstdlibDll;
  MODULEINFO miVstdlibDll;

	DWORD dwMaterialSystemDll;
  MODULEINFO miMaterialSystemDll;

  DWORD dwVGuiMatSurfaceDll;
  MODULEINFO miVGuiMatSurfaceDll;

  DWORD dwVGui2Dll;
  MODULEINFO miVGui2Dll;

  DWORD dwOverlayRendererDll;
  MODULEINFO miOverlayRendererDll;

  DWORD dwMatchMakingDll;
  MODULEINFO miMatchMakingDll;

  CreateInterfaceFn ciEngineInterface = nullptr;
  CreateInterfaceFn ciClientInterface = nullptr;
  CreateInterfaceFn ciServer = nullptr;
  CreateInterfaceFn ciVstdlibInterface = nullptr;
  CreateInterfaceFn ciMaterialSystem = nullptr;
  CreateInterfaceFn ciVGuiMatSurfaceInterface = nullptr;
  CreateInterfaceFn ciVGui2Interface = nullptr;
  CreateInterfaceFn ciOverlayRenderer = nullptr;

  SharedRandomFloatFn SharedRandomFloat;
  SetPredictionRandomSeedFn SetPredictionRandomSeed;

  //CreateMoveNewFn g_OrigCreateMoveNew;
  //BYTE g_jmp_p9[5] = { 0, 0, 0, 0, 0 };
  //BYTE g_codeFragment_p9[5] = { 0, 0, 0, 0, 0 };

  RandomFloat_t RandomFloat;
  RandomSeed_t RandomSeed;

  CUserCmd* pUserCmds[150];

  HWND hGameWindow;
  HDC HDC_Desktop;

  void* pSendPacket;

  Account user;

  long long int *m_plliSteamID;

  map<string, C_Cheat*> CheatsMap;

private:
	C_CheatMgr(HINSTANCE hInstanceDll);
	~C_CheatMgr();
};
