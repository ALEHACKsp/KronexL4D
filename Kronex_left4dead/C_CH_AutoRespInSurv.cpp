#include "KronexMain.h"

C_CH_AutoRespInSurv::C_CH_AutoRespInSurv(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_autoresp_enabled"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_autoresp_key_use"), XS("100"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_iPerformSleepTime = 5;
  m_bIsCheatInitialized = true;
}

C_CH_AutoRespInSurv::~C_CH_AutoRespInSurv()
{
  C_CVarMgr::UnRegConVar(XS("krx_autoresp_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_autoresp_key_use"));
}

void C_CH_AutoRespInSurv::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_autoresp_enabled"))->GetInt() == 1 ? true : false;
  m_iKeyCheatUse = C_CVarMgr::FindVar(XS("krx_autoresp_key_use"))->GetInt();
}

void C_CH_AutoRespInSurv::perform()
{
  if (GetAsyncKeyState(m_iKeyCheatUse))
  {
    if (m_pPlayer->Team() == TEAM_INFECT)
    {
      float oldCoords[2] = { m_pPlayer->Position()[0], m_pPlayer->Position()[1] };
      keybd_event(0x45, MapVirtualKeyEx(0x45, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
      while (Utils::Get2dDistance(m_pPlayer->Position(), oldCoords) < 2.0f);
      mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
      keybd_event(0x45, MapVirtualKeyEx(0x45, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
    }
  }
}

void C_CH_AutoRespInSurv::restoreChanges()
{

}
