#include "C_CH_NoSpread.h"

C_CH_NoSpread::C_CH_NoSpread(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_pbSpreadOriginBytes1 = "\x89\x46\x34\xE8\x1E\xBC\xFD\xFF\x8B\xC8\xE8\x87\xBF\xFD\xFF\x5F\x5E\x5D\x83\xC4\x14\xC2\x0C\x00";
  m_pbSpreadHackBytes1 = "\x90\x90\x90";
  m_dwSpreadFn1 = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x200000, m_pbSpreadOriginBytes1, "xxxxxxxxxxxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwSpreadFn1, 3, PAGE_EXECUTE_READWRITE, &m_dwSpreadFnOldProtect1);

  m_pbSpreadOriginBytes2 = "\xDD\xD8\xD9\x83\x38\x09\x00\x00\xD9\x9F\x74\x0C\x00\x00\x5B\x5F\x5E\x83\xC4\x08\xC3";
  m_pbSpreadHackBytes2 = "\xDD\xD8\xD9\x83\x38\x09\x00\x00\x90\x90\x90\x90\x90\x90\x5B\x5F\x5E\x83\xC4\x08\xC3";
  m_dwSpreadFn2 = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x300000, m_pbSpreadOriginBytes2, "xxxxxxxxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwSpreadFn2, 21, PAGE_EXECUTE_READWRITE, &m_dwSpreadFnOldProtect2);

  m_pbSpreadOriginBytes3 = "\xDD\xD8\xD9\x9F\x74\x0C\x00\x00\x5F\x5E\x5B\x83\xC4\x0C\xC3";
  m_pbSpreadHackBytes3 = "\xDD\xD8\x90\x90\x90\x90\x90\x90\x5F\x5E\x5B\x83\xC4\x0C\xC3";
  m_dwSpreadFn3 = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x300000, m_pbSpreadOriginBytes3, "xxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwSpreadFn3, 15, PAGE_EXECUTE_READWRITE, &m_dwSpreadFnOldProtect3);

  m_iPerformSleepTime = 1000;
  m_bIsCheatEnabled = TRUE;
  statusSwitched();
  m_bIsCheatInitialized = TRUE;
}

C_CH_NoSpread::~C_CH_NoSpread(VOID)
{
  VirtualProtect((LPVOID)m_dwSpreadFn1, 3, m_dwSpreadFnOldProtect1, NULL);
  VirtualProtect((LPVOID)m_dwSpreadFn2, 21, m_dwSpreadFnOldProtect2, NULL);
  VirtualProtect((LPVOID)m_dwSpreadFn3, 15, m_dwSpreadFnOldProtect3, NULL);
}

VOID C_CH_NoSpread::perform(VOID)
{
  
}

VOID C_CH_NoSpread::restoreChanges(VOID)
{
  *m_pCManager->m_piSvCheats = 0;
  *m_pCManager->m_piSvPure = 2;
  memcpy((PVOID)m_dwSpreadFn1, m_pbSpreadOriginBytes1, 3);
  memcpy((PVOID)m_dwSpreadFn2, m_pbSpreadOriginBytes2, 21);
  memcpy((PVOID)m_dwSpreadFn3, m_pbSpreadOriginBytes3, 15);
}

VOID C_CH_NoSpread::statusSwitched(VOID)
{
  if (m_bIsCheatEnabled)
  {
    *m_pCManager->m_piSvCheats = 1;
    *m_pCManager->m_piSvPure = 0;
    memcpy((PVOID)m_dwSpreadFn1, m_pbSpreadHackBytes1, 3);
    memcpy((PVOID)m_dwSpreadFn2, m_pbSpreadHackBytes2, 21);
    memcpy((PVOID)m_dwSpreadFn3, m_pbSpreadHackBytes3, 15);
  }
  else
  {
    restoreChanges();
  }
}
