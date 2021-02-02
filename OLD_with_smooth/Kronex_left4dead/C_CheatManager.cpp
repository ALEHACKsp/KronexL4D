#include "CONFIG.h"
#include "C_CheatManager.h"
#include "C_EntityManager.h"
#include "C_CH_BunnyHop.h"
#include "C_CH_GlowHack.h"
#include "C_CH_VisualHacks.h"
#include "C_CH_Aimbot.h"
#include "C_CH_Ceiling.h"
#include "C_CH_NoRecoil.h"
#include "C_CH_CameraHack.h"
#include "C_CH_RespInSurv.h"
#include "C_CH_ESP.h"
#include "C_CH_FakeLag.h"
#include "C_CH_NoSpread.h"

C_CheatManager* C_CheatManager::Instance = NULL;

DWORD C_CheatManager::main(HINSTANCE hInstanceDll)
{
	FreeConsole();
	AllocConsole();

	char str[256];
	sprintf(str, "%s %s\0", KRONEX_TITLE, KRONEX_VERSION);
	SetConsoleTitle(str);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	C_CheatManager* cheatManager = new C_CheatManager();

  while (cheatManager->CheatsList.size() > 0)
  {
    size_t cheatsCount = cheatManager->CheatsList.size();

    if (GetAsyncKeyState(KEY_DESTROY_ALL_CHEATS))
    {
      for each(C_Cheat* currentCheat in cheatManager->CheatsList)
      {
        if (!currentCheat->unload()) cout << "Unload failed: " << currentCheat->m_sCheatName.c_str() << endl;
      }
      cheatManager->CheatsList.clear();
      continue;
    }

    for each(C_Cheat* currentCheat in cheatManager->CheatsList)
    {
      if (GetAsyncKeyState(currentCheat->m_iKeyCheatSwitchStatus))
      {
        currentCheat->switchStatus();
      }
    }

    Sleep(5);
  }

  delete cheatManager;

	FreeConsole();
	fclose(stdout);
	fclose(stdin);

  FreeLibraryAndExitThread((HMODULE)hInstanceDll, 0);
  return 0;
}

C_CheatManager::C_CheatManager(VOID)
{
  m_GameWindow = FindWindow(NULL, "Left 4 Dead");
  m_HDC_Desktop = GetDC(m_GameWindow);

	m_dwEngineDll = (DWORD)GetModuleHandle("engine.dll");
	m_dwClientDll = (DWORD)GetModuleHandle("client.dll");
	m_dwServerDll = (DWORD)GetModuleHandle("server.dll");
	m_dwMaterialSystemDll = (DWORD)GetModuleHandle("materialsystem.dll");
  m_dwVguiMatSurfaceDll = (DWORD)GetModuleHandle("vguimatsurface.dll");
  m_dwOverlayRendererDll = (DWORD)GetModuleHandle("gameoverlayrenderer.dll");

  m_piCmdRate = (PINT)(m_dwEngineDll + 0x3CAAB8);
  m_pfCmdRate = (PFLOAT)(m_dwEngineDll + 0x3CAAB4);
  m_piUpdRate = (PINT)(m_dwEngineDll + 0x3CAB50);
  m_pfUpdRate = (PFLOAT)(m_dwEngineDll + 0x3CAB4C);

  m_pfPacketsLimiter = (PFLOAT)(m_dwEngineDll + 0x3B0398);
  m_piFlushEntityPacket = (PINT)(m_dwEngineDll + 0x40E888);
  m_piIgnorePackets = (PINT)(m_dwEngineDll + 0x41A088);
  m_pfNetBlockMsg = (PFLOAT)(m_dwEngineDll + 0x4018DC);
  m_piNetDropPackets = (PINT)(m_dwEngineDll + 0x4020E8);
  m_piNetFakeJitter = (PINT)(m_dwEngineDll + 0x4024B8);
  m_pfNetFakelag = (PFLOAT)(m_dwEngineDll + 0x4025FC);
  m_pfNetFakeloss = (PFLOAT)(m_dwEngineDll + 0x40246C);

  m_piSvCheats = (PINT)(m_dwEngineDll + 0x57A168);
  m_piSvConsistency = (PINT)(m_dwEngineDll + 0x57A3F0);
  m_pfSvConsistency = (PFLOAT)(m_dwEngineDll + 0x57A3EC);
  m_piSvPure = (PINT)(m_dwEngineDll + 0x563C64);

	m_piJump_Status = (PINT)(m_dwClientDll + 0x56DD58);
	m_piAttack_Status = (PINT)(m_dwClientDll + 0x56DD40);
	m_piAttack2_Status = (PINT)(m_dwClientDll + 0x56DD28);
	m_piDuck_Status = (PINT)(m_dwClientDll + 0x56DCE0);
	
  m_piIsPlayerOnServer = (PINT)(m_dwClientDll + 0x5C8185);
	m_piScreenResolution = (PINT)(m_dwEngineDll + 0x3B41C4);
	m_pbIsChatClosed = (PBYTE)(m_dwVguiMatSurfaceDll + 0x124044);
	m_piIsESCPressed = (PINT)(m_dwClientDll + 0x5BF428);
  m_piIsOverlayRendered = (PINT)(m_dwOverlayRendererDll + 0xEE828); // 0xEE828 // 0xEE978
	m_pfCrossHairController = (PFLOAT)(*(PDWORD)(m_dwEngineDll + 0x3B5C68) + 0x4AAC);
  m_pfMouseSensitivity = (PFLOAT)(m_dwClientDll + 0x56F284);

  m_pfWorldToScreenMatrix = (PFLOAT)(m_dwEngineDll + 0x5266A8);

	Instance = this;

  CheatsList.push_back(new C_CH_GlowHack(this, "C_CH_GlowHack"));
	CheatsList.push_back(new C_CH_VisualHacks(this, "C_CH_VisualHacks"));
	CheatsList.push_back(new C_CH_BunnyHop(this, "C_CH_BunnyHop"));
	CheatsList.push_back(new C_CH_Aimbot(this, "C_CH_Aimbot"));
  CheatsList.push_back(new C_CH_Ceiling(this, "C_CH_Ceiling"));
  CheatsList.push_back(new C_CH_NoRecoil(this, "C_CH_NoRecoil"));
  CheatsList.push_back(new C_CH_CameraHack(this, "C_CH_CameraHack"));
  //CheatsList.push_back(new C_CH_RespInSurv(this, "C_CH_RespInSurv"));
  CheatsList.push_back(new C_CH_ESP(this, "C_CH_ESP"));
  CheatsList.push_back(new C_CH_FakeLag(this, "C_CH_FakeLag"));
  //CheatsList.push_back(new C_CH_NoSpread(this, "C_CH_NoSpread")); // not working
}

C_CheatManager::~C_CheatManager(VOID)
{
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

BOOL C_CheatManager::CompareDataMask(PCHAR pData, PCHAR bMask, PCHAR szMask)
{
  for (/**/; *szMask; ++szMask, ++pData, ++bMask)
  {
    if (*szMask == 'x' && *pData != *bMask) return FALSE;
  }
  return (*szMask) == NULL;
}

DWORD C_CheatManager::FindPattern(DWORD dwStartAddress, DWORD dwLen, PCHAR bMask, PCHAR szMask)
{
  for (DWORD i = 0; i < dwLen; i++)
  {
    if (CompareDataMask((PCHAR)(dwStartAddress + i), bMask, szMask))
    {
      return (DWORD)(dwStartAddress + i);
    }
  }
  return 0;
}