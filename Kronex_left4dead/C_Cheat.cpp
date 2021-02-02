#include "KronexMain.h"

C_Cheat::C_Cheat(C_CheatMgr* cheatManager, string cheatName)
  : pCMgr(cheatManager),
    m_sCheatName(cheatName),
    m_bIsCheatInitialized(false)
{
  pPMgr = C_PatchMgr::Instance();
  pHMgr = C_VMTHookMgr::Instance();
  pCVarMgr = C_CVarMgr::Instance();

  pEMgr = new C_EntityMgr();
  m_pPlayer = pEMgr->m_pMyPlayer;

	m_bIsCheatEnabled = false;

	m_iPerformSleepTime = 1;
  m_iUpdateSleepTime = 100;
	m_iKeyCheatUse = NULL;

  m_bIsPerformThreadAlive = true;
	m_hPerformThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PerformLoop, this, NULL, NULL);

  m_bIsUpdateThreadAlive = true;
  m_hUpdateThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)UpdaterLoop, this, NULL, NULL);
}

C_Cheat::~C_Cheat()
{
  delete pEMgr;
}

bool C_Cheat::Unload()
{
  m_bIsCheatEnabled = false;
  m_iPerformSleepTime = 0;

  m_bIsCheatInitialized = false;

  if (m_hPerformThread)
  {
    if (!TerminateThread(m_hPerformThread, 0))
    {
      return false;
    }
    m_bIsPerformThreadAlive = false;
  }

  if (m_hUpdateThread)
  {
    if (!TerminateThread(m_hUpdateThread, 0))
    {
      return false;
    }
    m_bIsUpdateThreadAlive = false;
  }

  restoreChanges();

  return true;
}

void C_Cheat::Toggle()
{
  m_bIsCheatEnabled = !m_bIsCheatEnabled;
}

void C_Cheat::UpdaterLoop(C_Cheat* pCheat)
{
  while (pCheat->m_bIsUpdateThreadAlive)
  {
    if (pCheat->m_bIsCheatInitialized)
    {
      pCheat->update();
      this_thread::sleep_for(chrono::milliseconds(pCheat->m_iUpdateSleepTime));
    }
    else
    {
      this_thread::sleep_for(chrono::milliseconds(100));
    }
  }
}

void C_Cheat::PerformLoop(C_Cheat* pCheat)
{
	while (pCheat->m_bIsPerformThreadAlive)
	{
    if (pCheat->m_bIsCheatInitialized)
    {
      if (pCheat->m_bIsCheatEnabled)
      {
        pCheat->perform();
        pCheat->m_bIsCheatRestored = false;
      }
      else
      {
        if (!pCheat->m_bIsCheatRestored)
        {
          pCheat->restoreChanges();
          pCheat->m_bIsCheatRestored = true;
        }
      }

      this_thread::sleep_for(chrono::milliseconds(pCheat->m_iPerformSleepTime));
    }
    else
    {
      this_thread::sleep_for(chrono::milliseconds(100));
    }
	}
}

HANDLE C_Cheat::GetPerformThread()
{
	return m_hPerformThread;
}
