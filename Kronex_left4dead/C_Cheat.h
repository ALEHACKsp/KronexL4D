#pragma once

class C_Cheat
{
public:

	static void PerformLoop(C_Cheat* pCheat);
  static void UpdaterLoop(C_Cheat* pCheat);

	C_Cheat(C_CheatMgr* cheatManager, string cheatName);
	virtual ~C_Cheat();

  virtual void update() = 0;
	virtual void perform() = 0;
  virtual void restoreChanges() = 0;

	virtual void Toggle();
	virtual bool Unload();

	virtual HANDLE GetPerformThread();

  C_Player* m_pPlayer;

  C_CheatMgr* pCMgr;
  C_EntityMgr* pEMgr;
  C_PatchMgr* pPMgr;
  C_VMTHookMgr* pHMgr;
  C_CVarMgr* pCVarMgr;

  HANDLE m_hPerformThread;
  HANDLE m_hUpdateThread;

  bool m_bIsPerformThreadAlive;
  bool m_bIsUpdateThreadAlive;
  bool m_bIsCheatEnabled;
  bool m_bIsCheatRestored;

  int m_iPerformSleepTime;
  int m_iUpdateSleepTime;
  int m_iKeyCheatUse;

  string m_sCheatName;

protected:
  bool m_bIsCheatInitialized;
};

