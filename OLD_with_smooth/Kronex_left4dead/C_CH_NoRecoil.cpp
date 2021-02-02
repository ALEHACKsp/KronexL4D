#include "C_CH_NoRecoil.h"

C_CH_NoRecoil::C_CH_NoRecoil(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_pbRecoilOriginBytes = "\xD9\x07\xD8\x86\x6C\x0F\x00\x00\xD9\x1F\xD9\x86\x70\x0F\x00\x00\xD8\x47\x04\xD9\x5F\x04\xD9\x86\x74\x0F\x00\x00\xD8\x47\x08\xD9\x5F\x08";
  m_pbRecoilHackBytes = "\xD9\x07\x90\x90\x90\x90\x90\x90\xD9\x1F\xD9\x86\x70\x0F\x00\x00\xD8\x47\x04\xD9\x5F\x04\xD9\x86\x74\x0F\x00\x00\xD8\x47\x08\xD9\x5F\x08";

  m_dwRecoilFn = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x100000, m_pbRecoilOriginBytes, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwRecoilFn, 34, PAGE_EXECUTE_READWRITE, &m_dwRecoiFnOldProtect);

  m_iPerformSleepTime = 1000;
  m_bIsCheatEnabled = TRUE;
  statusSwitched();
  m_bIsCheatInitialized = TRUE;
}

C_CH_NoRecoil::~C_CH_NoRecoil(VOID)
{
  VirtualProtect((LPVOID)m_dwRecoilFn, 34, m_dwRecoiFnOldProtect, NULL);
}

VOID C_CH_NoRecoil::perform(VOID)
{

}

VOID C_CH_NoRecoil::restoreChanges(VOID)
{
  memcpy((PVOID)m_dwRecoilFn, m_pbRecoilOriginBytes, 34);
}

VOID C_CH_NoRecoil::statusSwitched(VOID)
{
  if (m_bIsCheatEnabled)
  {
    memcpy((PVOID)m_dwRecoilFn, m_pbRecoilHackBytes, 34);
  }
  else
  {
    restoreChanges();
  }
}
