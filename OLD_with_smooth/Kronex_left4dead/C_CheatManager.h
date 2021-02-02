#pragma once

class C_Player;
class C_Cheat;

#include <windows.h>
#include <vector>

#include "C_Cheat.h"
#include "C_Player.h"

class C_CheatManager
{
public:

	static DWORD main(HINSTANCE m_hInstanceDll);
	static C_CheatManager* Instance;

  BOOL CompareDataMask(PCHAR pData, PCHAR bMask, PCHAR szMask);
  DWORD FindPattern(DWORD dwStartAddress, DWORD dwLen, PCHAR bMask, PCHAR szMask);

	//C_EntityManager* pEManager;

	DWORD m_dwEngineDll;
	DWORD m_dwClientDll;
	DWORD m_dwServerDll;
	DWORD m_dwMaterialSystemDll;
  DWORD m_dwVguiMatSurfaceDll;
  DWORD m_dwOverlayRendererDll;

  PFLOAT m_pfPacketsLimiter;
  PINT m_piFlushEntityPacket;
  PINT m_piIgnorePackets;
  PFLOAT m_pfNetBlockMsg;
  PINT m_piNetDropPackets;
  PINT m_piNetFakeJitter;
  PFLOAT m_pfNetFakelag;
  PFLOAT m_pfNetFakeloss;

  PINT m_piCmdRate;
  PFLOAT m_pfCmdRate;
  PINT m_piUpdRate;
  PFLOAT m_pfUpdRate;

  PFLOAT m_pfSvConsistency;
  PINT m_piSvConsistency;
  PINT m_piSvCheats;
  PINT m_piSvPure;

	PINT m_piJump_Status;
	PINT m_piAttack_Status;
	PINT m_piAttack2_Status;
	PINT m_piDuck_Status;

	PINT m_piIsPlayerOnServer;
	PINT m_piScreenResolution;
	PINT m_piIsESCPressed;
  PINT m_piIsOverlayRendered;
  PBYTE m_pbIsChatClosed;
  
	PFLOAT m_pfCrossHairController;
  PFLOAT m_pfMouseSensitivity;
  PFLOAT m_pfWorldToScreenMatrix;

  HWND m_GameWindow;
  HDC m_HDC_Desktop;

private:
	C_CheatManager(VOID);
	~C_CheatManager(VOID);

	HINSTANCE m_hInstanceDll;

	vector<C_Cheat*> CheatsList;
};

