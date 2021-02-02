//#include "C_CH_GlowHack.h"
//
//C_CH_GlowHack::C_CH_GlowHack(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
//{
//  m_pcGlowHackFnSingature = "\xCC\xCC\x8B\x81\xBC\x00\x00\x00\x50\xE8\xA4\x1E\x05\x00\x83\xC4\x04\xC3\x8B\x81\xBC\x00\x00\x00\xC3\xCC\xCC";
//  m_pcGlowHackOrigin = "\x8B\x81\xBC\x00\x00\x00";
//  m_pcGlowHackSpec = "\xB8\x01\x00\x00\x00\x90";
//  m_pcGlowHackSurv = "\xB8\x02\x00\x00\x00\x90";
//  m_pcGlowHackInfect = "\xB8\x03\x00\x00\x00\x90";
//  m_dwGlowHackFn = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x100000, m_pcGlowHackFnSingature, "xxxxxxxxxxxxxxxxxxxxxxxxxxx");
//  m_dwGlowHackFn += 18;
//  VirtualProtect((LPVOID)m_dwGlowHackFn, 6, PAGE_EXECUTE_READWRITE, &m_dwGlowHackFnOldProtect);
//
//  m_pcDistanceFnSingature = "\xD8\xD1\xDF\xE0\xF6\xC4\x05\x7A\x04\xDD\xD9\xEB\x02\xDD\xD8\xD8\x55\x00\xDF\xE0\xF6\xC4\x05\x7A\x67";
//  m_pcDistanceFnOrigin = "\xDD\xD8";
//  m_pcDistanceFnHack = "\xDD\xD9";
//  m_dwDistanceFn = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x300000, m_pcDistanceFnSingature, "xxxxxxxxxxxxxxxxxxxxxxxxx");
//  m_dwDistanceFn += 13;
//  VirtualProtect((LPVOID)m_dwDistanceFn, 2, PAGE_EXECUTE_READWRITE, &m_dwDistanceFnOldProtect);
//
//  m_iKeyCheatSwitchStatus = VK_NUMPAD2;
//  m_iPerformSleepTime = 300;
//  m_bIsCheatEnabled = TRUE;
//  m_bIsCheatInitialized = TRUE;
//}
//
//C_CH_GlowHack::~C_CH_GlowHack(VOID)
//{
//  VirtualProtect((LPVOID)m_dwGlowHackFn, 6, m_dwGlowHackFnOldProtect, NULL);
//  VirtualProtect((LPVOID)m_dwDistanceFn, 2, m_dwDistanceFnOldProtect, NULL);
//}
//
//VOID C_CH_GlowHack::restoreChanges(VOID)
//{
//  memcpy((PVOID)m_dwGlowHackFn, (PVOID)m_pcGlowHackOrigin, 6);
//  memcpy((PVOID)m_dwDistanceFn, (PVOID)m_pcDistanceFnOrigin, 2);
//}
//
//VOID C_CH_GlowHack::perform(VOID)
//{
//  if (m_bIsCheatEnabled)
//  {
//    if (*m_pCManager->m_piIsPlayerOnServer == 1)
//    {
//      if (m_pMyPlayer->Team() == TeamSurv)
//        memcpy((PVOID)m_dwGlowHackFn, (PVOID)m_pcGlowHackSurv, 6);
//      else if (m_pMyPlayer->Team() == TeamSpec)
//        memcpy((PVOID)m_dwGlowHackFn, (PVOID)m_pcGlowHackInfect, 6);
//      else if (m_pMyPlayer->Team() == TeamInfect)
//        memcpy((PVOID)m_dwGlowHackFn, (PVOID)m_pcGlowHackOrigin, 6);
//
//      memcpy((PVOID)m_dwDistanceFn, (PVOID)m_pcDistanceFnHack, 2);
//    }
//  }
//  else
//  {
//    restoreChanges();
//  }
//}
//
//VOID C_CH_GlowHack::statusSwitched(VOID)
//{
//  if (!m_bIsCheatEnabled)
//  {
//    restoreChanges();
//  }
//}

#include "C_CH_GlowHack.h"

C_CH_GlowHack::C_CH_GlowHack(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_pcDistanceFnSingature = "\xD8\xD1\xDF\xE0\xF6\xC4\x05\x7A\x04\xDD\xD9\xEB\x02\xDD\xD8\xD8\x55\x00\xDF\xE0\xF6\xC4\x05\x7A\x67";
  m_pcDistanceFnOrigin = "\xDD\xD8";
  m_pcDistanceFnHack = "\xDD\xD9";
  m_dwDistanceFnOffset = 0xD;

  m_dwDistanceFn = m_pCManager->FindPattern(m_pCManager->m_dwClientDll, 0x300000, m_pcDistanceFnSingature, "xxxxxxxxxxxxxxxxxxxxxxxxx");
  m_dwDistanceFn += m_dwDistanceFnOffset;
  VirtualProtect((LPVOID)m_dwDistanceFn, 2, PAGE_EXECUTE_READWRITE, &m_dwDistanceFnOldProtect);

  m_iKeyCheatSwitchStatus = VK_NUMPAD2;
  m_iPerformSleepTime = 250;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_GlowHack::~C_CH_GlowHack(VOID)
{
  VirtualProtect((LPVOID)m_dwDistanceFn, 2, m_dwDistanceFnOldProtect, NULL);
}

VOID C_CH_GlowHack::restoreChanges(VOID)
{
  if (*m_pCManager->m_piIsPlayerOnServer == 1)
  {
    int entitiesCount = m_pEManager->EntityList.size();
    m_pMyPlayer->SetTeam(m_pMyPlayer->Team());

    for (int i = 0; i < entitiesCount; i++)
    {
      C_Player* tempTarget = m_pEManager->EntityList[i];
      tempTarget->SetTeam(tempTarget->Team());
    }
  }
  memcpy((PVOID)m_dwDistanceFn, (PVOID)m_pcDistanceFnOrigin, 2);
}

VOID C_CH_GlowHack::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    if (*m_pCManager->m_piIsPlayerOnServer == 1)
    {
      int entitiesCount = m_pEManager->EntityList.size();

      for (int i = 0; i < entitiesCount; i++)
      {
        C_Player* tempPlayer = m_pEManager->EntityList[i];

        if (tempPlayer->Team() == TeamInfect && m_pMyPlayer->Team() == TeamSurv)
        {
          tempPlayer->SetTeam(TeamSurv);
        }
        else
        {
          tempPlayer->SetTeam(tempPlayer->Team());
        }
      }
    }
    memcpy((PVOID)m_dwDistanceFn, (PVOID)m_pcDistanceFnHack, 2);
  }
}

VOID C_CH_GlowHack::statusSwitched(VOID)
{
  if (!m_bIsCheatEnabled)
  {
    restoreChanges();
  }
}