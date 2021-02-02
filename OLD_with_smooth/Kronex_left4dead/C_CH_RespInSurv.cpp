#include "C_CH_RespInSurv.h"

C_CH_RespInSurv::C_CH_RespInSurv(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_iPerformSleepTime = 2;
  m_iKeyCheatUse = VK_NUMPAD4;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_RespInSurv::~C_CH_RespInSurv(VOID)
{

}

VOID C_CH_RespInSurv::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    if (GetAsyncKeyState(m_iKeyCheatUse))
    {
      if (m_pMyPlayer->Team() == TeamInfect)
      {
        float oldCoords[2] = { m_pMyPlayer->Position()[0], m_pMyPlayer->Position()[1] };
        keybd_event(0x45, MapVirtualKeyEx(0x45, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
        while (StaticFunctions::Get2dDistance(m_pMyPlayer->Position(), oldCoords) < 2.0f);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        keybd_event(0x45, MapVirtualKeyEx(0x45, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
      }
      
    }
  }
}

VOID C_CH_RespInSurv::restoreChanges(VOID)
{

}

VOID C_CH_RespInSurv::statusSwitched(VOID)
{

}
