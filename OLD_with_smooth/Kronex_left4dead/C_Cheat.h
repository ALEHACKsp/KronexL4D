#pragma once

using namespace std;

class C_CheatManager;
class C_EntityManager;
class C_Player;

#include <windows.h>
#include <iostream>
#include <thread>
#include <ctime>

#include "CONSTATNS.h"
#include "C_CheatManager.h"
#include "C_EntityManager.h"
#include "C_Player.h"
#include "StaticFunctions.h"

class C_Cheat
{
public:

	static DWORD startNewThread(C_Cheat* pCheat);

	C_Cheat(C_CheatManager* cheatManager, string cheatName);
	virtual ~C_Cheat(VOID);

	virtual VOID perform(VOID) = 0;
	virtual VOID restoreChanges(VOID) = 0;
	virtual VOID statusSwitched(VOID) = 0;

	virtual VOID switchStatus(VOID);
	virtual BOOL unload(VOID);

	virtual HANDLE getThreadHandle(VOID);

  static C_Cheat* Instance;

  C_Player* m_pMyPlayer;

  C_CheatManager* m_pCManager;
  C_EntityManager* m_pEManager;

  HANDLE m_hThreadHandle;

  BOOL m_bIsThreadAlive;
  BOOL m_bIsCheatEnabled;

  INT m_iPerformSleepTime;
  INT m_iKeyCheatSwitchStatus;
  INT m_iKeyCheatUse;
  INT m_iTimeSinceLastSwitch;

  string m_sCheatName;

protected:
  BOOL m_bIsCheatInitialized;
};

