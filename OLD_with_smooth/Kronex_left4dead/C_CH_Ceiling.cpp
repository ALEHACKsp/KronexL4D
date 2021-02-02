#include "C_CH_Ceiling.h"

C_CH_Ceiling::C_CH_Ceiling(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_iLastClickTimer = clock();

  m_pbMouseOriginBytes = "\xD9\x80\xA4\x4A\x00\x00\x8B\x4C\x24\x08\x05\xA4\x4A\x00\x00\xD9\x19";
  m_pbMouseHackBytes = "\x8B\x4C\x24\x08\x05\xA4\x4A\x00\x00\xD9\xEB\xD8\xC0\xD8\xC0\xD9\x19";

  m_dwAngleControllerFn = m_pCManager->FindPattern(m_pCManager->m_dwEngineDll, 0x100000, m_pbMouseOriginBytes, "xxxxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwAngleControllerFn, 17, PAGE_EXECUTE_READWRITE, &m_dwAngleControllerFnOldProtect);

  m_iPerformSleepTime = 2;
  m_iKeyCheatUse = VK_CAPITAL;
  m_bIsCeilingNow = FALSE;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_Ceiling::~C_CH_Ceiling(VOID)
{
  VirtualProtect((LPVOID)m_dwAngleControllerFn, 17, m_dwAngleControllerFnOldProtect, NULL);
}

VOID C_CH_Ceiling::restoreChanges(VOID)
{
  memcpy((PVOID)m_dwAngleControllerFn, (PVOID)m_pbMouseOriginBytes, 17);
}

VOID C_CH_Ceiling::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    if (*m_pCManager->m_piIsPlayerOnServer == 1
        && *m_pCManager->m_pbIsChatClosed == 1
        && *m_pCManager->m_piIsESCPressed == 0
        && *m_pCManager->m_piIsOverlayRendered == 0)
    {
      if (GetAsyncKeyState(m_iKeyCheatUse))
      {
        if (m_pMyPlayer > 0
            && m_pMyPlayer->Team() == TeamInfect
            && m_pMyPlayer->CharType() == CharacterType_HUNTER
            && m_pMyPlayer->IsAlive())
        {
          if (!m_bIsCeilingNow)
          {
            memcpy((PVOID)m_dwAngleControllerFn, m_pbMouseHackBytes, 17);
            m_bIsCeilingNow = TRUE;
          }
          if (clock() - m_iLastClickTimer > 50)
          {
            *m_pCManager->m_piAttack_Status = DoAction;
            //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            m_iLastClickTimer = clock();
          }
        }
      }
      else
      {
        if (m_bIsCeilingNow)
        {
          memcpy((PVOID)m_dwAngleControllerFn, m_pbMouseOriginBytes, 17);
          m_bIsCeilingNow = FALSE;
        }
      }
    }
  }
}

VOID C_CH_Ceiling::statusSwitched(VOID)
{
  if (!m_bIsCheatEnabled)
  {
    memcpy((PVOID)m_dwAngleControllerFn, m_pbMouseOriginBytes, 17);
    m_bIsCeilingNow = FALSE;
  }
}
