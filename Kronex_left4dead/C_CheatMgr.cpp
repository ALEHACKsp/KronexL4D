#include "KronexMain.h"

C_CheatMgr* C_CheatMgr::Instance = NULL;

IMoveHelper* g_pMoveHelper;
IEngineTrace* g_pEngineTrace;
IGameMovement* g_pGameMovement;
IPrediction* g_pPrediction;
IClientMode* g_pClientMode;
IClientEntityList* g_pEntList;
CBaseEntityList* g_pEntityList;
CGlobalVarsBase* g_pGlobalsClient;
IVEngineClientMy* g_pEngineClient;
IBaseClientDLL* g_pClient;
IMaterialSystem* g_pMaterialSystem;
IVDebugOverlay* g_pDebugOverlay;
IVModelInfoClient* g_pModelInfo;
IVModelRender* g_pModelRender;
IVRenderView* g_pRender;
IClientDLLSharedAppSystems* g_pClientSharedSystems;
CUserCmd* pCmd;
vgui::ISurface* g_pSurface;
vgui::IPanel* g_pPanel;
vgui::ISystem* g_pSystem;
vgui::IInput* g_pIInput;
vgui::IVGui* g_pVGui;

C_Cheat* C_CheatMgr::GetCheat(const string &cheatName)
{
  if (Instance->CheatsMap.empty())
  {
    return NULL;
  }

  auto iterator = Instance->CheatsMap.find(cheatName);
  if (iterator == Instance->CheatsMap.end())
  {
    return NULL;
  }

  return iterator->second;
}

DWORD C_CheatMgr::main(HINSTANCE hInstanceDll)
{
	FreeConsole();
	AllocConsole();

	char str[256];
  sprintf(str, "%s %s\0", XS(KRONEX_TITLE), 
#ifdef DEBUG
    XS(KRONEX_VERSION " DEBUG")
#else
    XS(KRONEX_VERSION)
#endif
  );
  
	SetConsoleTitle(str);
	freopen(XS("CONOUT$"), XS("w"), stdout); // kronex.log // CONOUT$
	freopen(XS("CONIN$"), XS("r"), stdin);

	C_CheatMgr* pCMgr = new C_CheatMgr(hInstanceDll);

  try
  {
    ConVar* krxEnabledVar = C_CVarMgr::FindVar(XS("krx_kronex_enabled"));

    while (!GetAsyncKeyState(KEY_DESTROY_ALL_CHEATS) && krxEnabledVar->GetInt() == 1)
    {
      if (pCMgr->user.sName == ACC_ASTARION.sName)
      {
        C_CVarMgr::FindVar(XS("cl_detaildist"))->SetValue(XS("0.01488"));
      }

      C_CVarMgr::FindVar(XS("krx_version"))->SetValue(XS("" KRONEX_VERSION));
      C_CVarMgr::FindVar(XS("krx_user_nickname"))->SetValue(pCMgr->user.sName.c_str());
      C_CVarMgr::FindVar(XS("krx_user_expire"))->SetValue(pCMgr->user.GetExpire().c_str());
      
      this_thread::sleep_for(chrono::milliseconds(5));
    }

    C_Cheat* pCurrentCheat;
    for (auto iterator = pCMgr->CheatsMap.begin(); iterator != pCMgr->CheatsMap.end(); ++iterator)
    {
      pCurrentCheat = iterator->second;
      if (!pCurrentCheat->Unload())
      {
        if (pCMgr->user.bDebugInformation)
        {
          cout << XS("Unload failed: ") << pCurrentCheat->m_sCheatName << endl;
        }
      }
      delete pCurrentCheat;
      pCurrentCheat = NULL;
    }
    pCMgr->CheatsMap.clear();

    delete pCMgr;
  }
  catch (int e)
  {
    if (pCMgr->user.bDebugInformation)
    {
      cout << XS("Main error: ") << hex << e << endl;
    }
  }

	FreeConsole();
	fclose(stdout);
	fclose(stdin);

  FreeLibraryAndExitThread((HMODULE)hInstanceDll, 0);
  return NULL;
}

void C_CheatMgr::KronexCmdExecFn(IConVar* var, const char *pOldValue, float flOldValue)
{
  ConVar* pCvar = (ConVar*)var;
  if (string(pCvar->GetString()) != string(pCvar->GetDefault()))
  {
    g_pEngineClient->ExecCMD(pCvar->GetString());
  }
}

void C_CheatMgr::KronexCmdExecCvarFn(IConVar* var, const char *pOldValue, float flOldValue)
{
  ConVar* pCvar = (ConVar*)var;
  if (string(pCvar->GetString()) != string(pCvar->GetDefault()))
  {
    string sInput = pCvar->GetString();

    vector<string> params = Utils::split_S8(sInput, XS(" "));

    if (params.size() >= 2)
    {
      if (!C_CVarMgr::SetInternalValue(params[0], params[1]))
      {
        if (C_CheatMgr::Instance->user.bDebugInformation)
        {
          cout << XS("Kronex SetInternalValue() failed!") << endl;
        }
      }
    }
  }
}

C_CheatMgr::C_CheatMgr(HINSTANCE hInstanceDll)
  : user(KRONEX_USER)
{
  if (!Instance) Instance = this;
  m_hInstanceDll = hInstanceDll;

  // Handles
  hCurProcess = GetCurrentProcess();
  hGameWindow = FindWindow(NULL, XS(GAME_WINDOW_NAME));
  HDC_Desktop = GetDC(hGameWindow);

  // Modules
	dwEngineDll = (DWORD)GetModuleHandle(XS("engine.dll"));
	dwClientDll = (DWORD)GetModuleHandle(XS("client.dll"));
	dwServerDll = (DWORD)GetModuleHandle(XS("server.dll"));
  dwVstdlibDll = (DWORD)GetModuleHandle(XS("vstdlib.dll"));
	dwMaterialSystemDll = (DWORD)GetModuleHandle(XS("materialsystem.dll"));
  dwMatchMakingDll = (DWORD)GetModuleHandle(XS("matchmaking.dll"));
  dwVGuiMatSurfaceDll = (DWORD)GetModuleHandle(XS("vguimatsurface.dll"));
  dwVGui2Dll = (DWORD)GetModuleHandle(XS("vgui2.dll"));
  dwOverlayRendererDll = (DWORD)GetModuleHandle(XS("gameoverlayrenderer.dll"));

  // Modules information
  GetModuleInformation(hCurProcess, (HMODULE)dwEngineDll, &miEngineDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwClientDll, &miClientDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwServerDll, &miServerDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwVstdlibDll, &miVstdlibDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwMaterialSystemDll, &miMaterialSystemDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwMatchMakingDll, &miMatchMakingDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwVGuiMatSurfaceDll, &miVGuiMatSurfaceDll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwVGui2Dll, &miVGui2Dll, sizeof(MODULEINFO));
  GetModuleInformation(hCurProcess, (HMODULE)dwOverlayRendererDll, &miOverlayRendererDll, sizeof(MODULEINFO));

  // Objects, offsets
  g_pGlobalsClient = (CGlobalVarsBase*)(dwEngineDll + 0x3B59B4);
  m_plliSteamID = (long long int *)(*(DWORD*)(dwMatchMakingDll + 0x51A18) + 0x8);

  // CUserCmd
  for (DWORD i = 0, userCmdBase = *(DWORD*)(*(DWORD*)(dwClientDll + 0x511FE4) + 0xD4); i < 150; i++)
  {
    pUserCmds[i] = (CUserCmd*)userCmdBase;
    userCmdBase += 0x58;
  }

  // INTERFACES
  ciClientInterface = (CreateInterfaceFn)((GetProcAddress((HMODULE)dwClientDll, XS("CreateInterface"))));

  g_pClient = SearchInterface<IBaseClientDLL*>(ciClientInterface, XS("VClient"));
  //g_pClientMode = **(IClientMode***)((*(uintptr_t**)g_pClient)[10] + 0x5);
  g_pClientSharedSystems = SearchInterface<IClientDLLSharedAppSystems*>(ciClientInterface, XS("VClientDllSharedAppSystems"));
  g_pEntList = SearchInterface<IClientEntityList*>(ciClientInterface, XS("VClientEntityList"));
  g_pEntityList = (CBaseEntityList*)g_pEntList;
  g_pGameMovement = SearchInterface<IGameMovement*>(ciClientInterface, XS("GameMovement"));
  g_pPrediction = SearchInterface<IPrediction*>(ciClientInterface, XS("VClientPrediction"));

  ciEngineInterface = (CreateInterfaceFn)(GetProcAddress((HMODULE)dwEngineDll, XS("CreateInterface")));
  g_pEngineClient = SearchInterface<IVEngineClientMy*>(ciEngineInterface, XS("VEngineClient"));
  g_pEngineTrace = SearchInterface<IEngineTrace*>(ciEngineInterface, XS("EngineTraceClient"));
  g_pDebugOverlay = SearchInterface<IVDebugOverlay*>(ciEngineInterface, XS("VDebugOverlay"));
  g_pModelInfo = SearchInterface<IVModelInfoClient*>(ciEngineInterface, XS("VModelInfoClient"));
  g_pModelRender = SearchInterface<IVModelRender*>(ciEngineInterface, XS("VEngineModel"));
  g_pRender = SearchInterface<IVRenderView*>(ciEngineInterface, XS("VEngineRenderView"));

  ciVGuiMatSurfaceInterface = (CreateInterfaceFn)(GetProcAddress((HMODULE)dwVGuiMatSurfaceDll, XS("CreateInterface")));
  g_pSurface = SearchInterface<vgui::ISurface*>(ciVGuiMatSurfaceInterface, XS("VGUI_Surface"));

  ciVGui2Interface = (CreateInterfaceFn)(GetProcAddress((HMODULE)dwVGui2Dll, XS("CreateInterface")));
  g_pPanel = SearchInterface<vgui::IPanel*>(ciVGui2Interface, XS("VGUI_Panel"));
  g_pSystem = SearchInterface<vgui::ISystem*>(ciVGui2Interface, XS("VGUI_System"));
  g_pIInput = SearchInterface<vgui::IInput*>(ciVGui2Interface, XS("VGUI_Input"));
  g_pVGui = SearchInterface<vgui::IVGui*>(ciVGui2Interface, XS("VGUI_ivgui"));
  
  ciVstdlibInterface = (CreateInterfaceFn)GetProcAddress((HMODULE)dwVstdlibDll, XS("CreateInterface"));
  RandomFloat = (RandomFloat_t)GetProcAddress((HMODULE)dwVstdlibDll, XS("RandomFloat"));
  RandomSeed = (RandomSeed_t)GetProcAddress((HMODULE)dwVstdlibDll, XS("RandomSeed"));
  g_pCVar = SearchInterface<ICvar*>(ciVstdlibInterface, XS("VEngineCvar"));

  ciMaterialSystem = (CreateInterfaceFn)GetProcAddress((HMODULE)dwMaterialSystemDll, XS("CreateInterface"));
  g_pMaterialSystem = SearchInterface<IMaterialSystem*>(ciMaterialSystem, XS("VMaterialSystem"));

  //g_pClientMode = GetClientModeNormal();
  
  // OTHER FUNCTIONS
  SharedRandomFloat = (SharedRandomFloatFn)(dwClientDll + 0x16CB80); // ne verno! 170717

  // PATCHES
  pSendPacket = Utils::FindPattern(
    Modules::Engine, XS("C6 44 24 07 01 FF D2 84 C0 74 12 80 BE 5C 4A 00 00 00 0F 84 15 04 00 00 C6 44 24 07 00 8B 4E 10 8B 01 8B 50 18 FF D2 84 C0 74 0B"),
    XS("pSendPacket"), 4);
  C_PatchMgr::RegPatch(pSendPacket, XS("00"), XS("pSendPacket"));

  // PATTERN-FUNCTIONS
  SetPredictionRandomSeed = Utils::FindPattern<SetPredictionRandomSeedFn>(
    Modules::Client, XS("8B 44 24 04 85 C0 75 0B C7 05 C0 D1 ?? ?? FF FF FF FF C3 8B 40 34 A3 C0 D1 ?? ?? C3 CC CC CC CC"),
    XS("SetPredictionRandomSeed"), 0);

  //g_OrigCreateMoveNew = Utils::FindPattern<CreateMoveNewFn>(
  //  Modules::Client, XS("5E C3 CC CC CC CC 6A FF ?? ?? ?? ?? ?? 83 C4 04 85 C0 ?? ?? B0 01 C2 08 00 8B 4C 24 08 D9 44 24 04 8B 10 8B 92 C0 03 00 00 51 51 8B C8 D9 1C 24 FF D2 C2 08 00 CC"),
  //  XS("CreateMoveNew"), 6);

  //g_jmp_p9[0] = 0xE9;
  //DWORD addr = (DWORD)Hooks::CreateMoveNew - (DWORD)g_OrigCreateMoveNew - 5;
  //memcpy(g_jmp_p9 + 1, &addr, sizeof(DWORD));
  //memcpy(g_codeFragment_p9, g_OrigCreateMoveNew, 5);
  //DWORD g_savedProtection_p9 = 0;
  //VirtualProtect(g_OrigCreateMoveNew, 8, PAGE_EXECUTE_READWRITE, &g_savedProtection_p9);
  //memcpy(g_OrigCreateMoveNew, g_jmp_p9, 5);

  // PATTERN-OBJECTS
  g_pMoveHelper = Utils::FindPattern<IMoveHelper*>(
    Modules::Client, XS("8B 0D ?? ?? ?? ?? 8B 54 24 0C 51 8B C4 89 10 8B 01"),
    XS("g_pMoveHelper"), 2);

  // HOOKS
  C_VMTHookMgr::AddVMTHook(g_pClient, 20, Hooks::IBaseClientDLL_CreateMove, XS("IBaseClientDLL_CreateMove"));
  C_VMTHookMgr::ApplyHook(XS("IBaseClientDLL_CreateMove"));

  C_VMTHookMgr::AddVMTHook(g_pPanel, 41, Hooks::IPanel_PaintTraverse, XS("IPanel_PaintTraverse"));
  C_VMTHookMgr::ApplyHook(XS("IPanel_PaintTraverse"));

  C_VMTHookMgr::AddVMTHook(g_pGameMovement, 1, Hooks::IGameMovement_ProcessMovement, XS("IGameMovement_ProcessMovement"));
  C_VMTHookMgr::ApplyHook(XS("IGameMovement_ProcessMovement"));

  C_VMTHookMgr::AddVMTHook(g_pPrediction, 19, Hooks::IPrediction_SetupMove, XS("IPrediction_SetupMove"));
  C_VMTHookMgr::ApplyHook(XS("IPrediction_SetupMove"));
  C_VMTHookMgr::AddVMTHook(g_pPrediction, 20, Hooks::IPrediction_FinishMove, XS("IPrediction_FinishMove"));
  C_VMTHookMgr::ApplyHook(XS("IPrediction_FinishMove"));

  C_VMTHookMgr::AddVMTHook(g_pEngineTrace, 5, Hooks::IEngineTrace_TraceRay, XS("IEngineTrace_TraceRay"));
  C_VMTHookMgr::ApplyHook(XS("IEngineTrace_TraceRay"));

  //C_VMTHookMgr::AddVMTHook(g_pModelRender, 2, Hooks::IVModelRender_DrawModel, XS("IVModelRender_DrawModel"));
  //C_VMTHookMgr::ApplyHook(XS("IVModelRender_DrawModel"));
  
  //C_VMTHookMgr::AddVMTHook(g_pModelRender, 18, Hooks::IVModelRender_DrawModelExecute, XS("IVModelRender_DrawModelExecute"));
  //C_VMTHookMgr::ApplyHook(XS("IVModelRender_DrawModelExecute"));

  //cout << "g_pClientMode: " << hex << g_pClientMode << endl;
  //cout << "CreateMoveNew: " << hex << Hooks::CreateMoveNew << endl;
  //bool (IClientMode::*haha)(float, CUserCmd*) = &IClientMode::CreateMove;
  //haha = &g_pClientMode->CreateMove;
  //if (g_pClientMode) cout << "g_pClientMode->CreateMove: " << hex << haha << endl;
  //CreateMoveNewFn fn = g_pClientMode->CreateMove;//(g_pClientMode->CreateMove);
  //C_VMTHookMgr::AddStdVMTHook(g_pClientMode, fn, 50, Hooks::CreateMoveNew, XS("CreateMoveNew"));
  //C_VMTHookMgr::ApplyHook(XS("CreateMoveNew"));

  // CONSOLE VARIABLES
  C_CVarMgr::RegConVar(XS("krx_kronex_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_version"), XS("" KRONEX_VERSION), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_user_nickname"), user.sName.c_str(), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_user_expire"), user.GetExpire().c_str(), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_exec"), XS("echo Hello, Kronex!"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN, C_CheatMgr::KronexCmdExecFn);
  C_CVarMgr::RegConVar(XS("krx_cvar"), XS("sv_cheats 1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN, C_CheatMgr::KronexCmdExecCvarFn);
  
  // CHEATS
#define REG_CHEAT(CHEAT) CheatsMap.insert(pair<string, C_Cheat*>(XS("" #CHEAT), new CHEAT(this, XS("" #CHEAT))))
  REG_CHEAT(C_CH_LicenseChecker);
  if (user.iCheats & CH_BHOP) REG_CHEAT(C_CH_BunnyHop);
  if (user.iCheats & CH_AIMBOT) REG_CHEAT(C_CH_Aimbot);
  if (user.iCheats & CH_GLOWHACK) REG_CHEAT(C_CH_GlowHack);
  //if (user.iCheats & CH_MATHACK) REG_CHEAT(C_CH_MaterialHack);
  if (user.iCheats & CH_CEILING) REG_CHEAT(C_CH_Ceiling);
  if (user.iCheats & CH_NORECOIL) REG_CHEAT(C_CH_NoRecoil);
  if (user.iCheats & CH_ESP) REG_CHEAT(C_CH_ESP); 
  if (user.iCheats & CH_RADAR) REG_CHEAT(C_CH_Radar);
  if (user.iCheats & CH_FAKELAG) REG_CHEAT(C_CH_FakeLag);
  if (user.iCheats & CH_TELEPORTANDCRUSH && user.sName == ACC_ASTARION.sName) REG_CHEAT(C_CH_TeleportAndCrush);
  if (user.iCheats & CH_NAMESTEALER) REG_CHEAT(C_CH_NameStealer);
  if (user.iCheats & CH_AUTORESP) REG_CHEAT(C_CH_AutoRespInSurv);
  if (user.iCheats != CH_NOTHING) REG_CHEAT(C_CH_ConfigExecuter);
  
  g_pCVar->ConsoleColorPrintf(Color(0, 255, 255, 255), XS("%s(%s) was injected!\n"), XS(KRONEX_TITLE), XS(KRONEX_VERSION));

  Beep(1200, 150);
}

C_CheatMgr::~C_CheatMgr()
{
  //BYTE* codeDest = (BYTE*)g_OrigCreateMoveNew;
  //codeDest[0] = g_codeFragment_p9[0];
  //*((DWORD*)(codeDest + 1)) = *((DWORD*)(g_codeFragment_p9 + 1));

  delete C_PatchMgr::Instance();
  delete C_VMTHookMgr::Instance();
  delete C_CVarMgr::Instance();

  g_pCVar->ConsoleColorPrintf(Color(255, 255, 0, 255), XS("%s(%s) was unloaded!\n"), XS(KRONEX_TITLE), XS(KRONEX_VERSION));
  Beep(600, 400);

	//Beep(380, 110); // Mc.Donald's
	//Beep(430, 130);
	//Beep(480, 150);
	//Beep(630, 150);
	//Beep(570, 500);
	//Beep(510, 140);
	//Beep(510, 150);
	//Beep(480, 140);
	//Beep(380, 280);
}

void C_CheatMgr::SendPacketStatus(bool bSendPacketStatus) const
{
  if (bSendPacketStatus)
  {
    C_PatchMgr::RestorePatch(XS("pSendPacket"));
  }
  else
  {
    C_PatchMgr::ApplyPatch(XS("pSendPacket"));
  }
}

template <typename T> T C_CheatMgr::SearchInterface(CreateInterfaceFn factory, string name)
{
  string sInputIFaceName = name;

  name += XS("000");
  size_t namelen = name.length();
  void* pInterface;

  for(int i = 0; i < 100; i++)
  {
    for (size_t j = namelen - 1; j >= namelen - 3; j--)
    {
      if (name[j] == '9')
      {
        name[j] = '0';
      }
      else
      {
        name[j]++;
        break;
      }
    }

    pInterface = (void*)factory(name.c_str(), NULL);
    if (pInterface != NULL) return static_cast<T>(pInterface);
  }

  if (user.bDebugInformation)
  {
    cout << XS("Interface not found! [") << sInputIFaceName << XS("]") << endl;
  }
  return NULL;
}
