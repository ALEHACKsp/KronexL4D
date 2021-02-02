#include "C_Cheat.h"
#include "CONFIG.h"

C_Cheat* C_Cheat::Instance = NULL;

C_Cheat::C_Cheat(C_CheatManager* cheatManager, string cheatName)
{
  Instance = this;

  m_bIsCheatInitialized = FALSE;
  //*(PDWORD)0x52 = 0x235426; // for crush

	m_pCManager = cheatManager;
  m_sCheatName = cheatName;
  m_pEManager = new C_EntityManager();
  m_pMyPlayer = m_pEManager->m_pMyPlayer;

	m_bIsThreadAlive = TRUE;
	m_bIsCheatEnabled = TRUE;

	m_iPerformSleepTime = 1;
	m_iKeyCheatSwitchStatus = KEY_STANDART_CHEAT_SWITCH_STATUS;
	m_iKeyCheatUse = KEY_STANDART_CHEAT_USE;

	m_iTimeSinceLastSwitch = clock();

	m_hThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startNewThread, this, NULL, NULL);
}

C_Cheat::~C_Cheat(VOID)
{
  delete m_pEManager;
}

BOOL C_Cheat::unload(VOID)
{
  m_iPerformSleepTime = 0;
  m_bIsCheatEnabled = FALSE;
  m_bIsCheatInitialized = FALSE;

  restoreChanges();

  m_bIsThreadAlive = FALSE;

  if (!TerminateThread(m_hThreadHandle, 0)) return FALSE;

  //CloseHandle(m_hThreadHandle);
  //m_hThreadHandle = NULL;

  return TRUE;
}

VOID C_Cheat::switchStatus(VOID)
{
	if (clock() - m_iTimeSinceLastSwitch > TIME_MS_CHEAT_SWITCH_STATUS)
	{
		m_bIsCheatEnabled = !m_bIsCheatEnabled;
		statusSwitched();
		m_iTimeSinceLastSwitch = clock();
	}
}

DWORD C_Cheat::startNewThread(C_Cheat* pCheat)
{
	while (pCheat->m_bIsThreadAlive)
	{
    if (pCheat->m_bIsCheatInitialized)
    {
      /*if (pCheat->m_bIsThreadAlive) */pCheat->perform();
      if(pCheat->m_iPerformSleepTime > 0) this_thread::sleep_for(chrono::milliseconds(pCheat->m_iPerformSleepTime));
    }
	}

	return 0;
}

HANDLE C_Cheat::getThreadHandle(VOID)
{
	return m_hThreadHandle;
}
