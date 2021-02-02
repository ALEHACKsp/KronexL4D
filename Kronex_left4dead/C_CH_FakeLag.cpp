#include "KronexMain.h"

C_CH_FakeLag::C_CH_FakeLag(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_fakelag_enabled"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_iPerformSleepTime = 5;
  m_bIsLagging = false;
  m_bIsCheatInitialized = true;
}

C_CH_FakeLag::~C_CH_FakeLag()
{
  C_CVarMgr::UnRegConVar(XS("krx_fakelag_enabled"));
}

void C_CH_FakeLag::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_fakelag_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_FakeLag::perform()
{
  if (IS_EXEC_ALLOWED)
  {
    if (m_pPlayer->Team() == TEAM_INFECT
        && m_pPlayer->CharType() == CHARACTER_TYPE_HUNTER
        && m_pPlayer->IsAlive()
        && m_pPlayer->IsSpawned())
    {
      m_bIsLagging = true;

      pCMgr->SendPacketStatus(false);
      this_thread::sleep_for(chrono::milliseconds(105)); // 100

      pCMgr->SendPacketStatus(true);
      this_thread::sleep_for(chrono::milliseconds(15)); // 20
    }
    else
    {
      if (m_bIsLagging)
      {
        pCMgr->SendPacketStatus(true);
        m_bIsLagging = false;
      }
    }
  }
}

void C_CH_FakeLag::restoreChanges()
{
  pCMgr->SendPacketStatus(true);
}
