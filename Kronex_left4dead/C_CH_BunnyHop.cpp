#include "KronexMain.h"

C_CH_BunnyHop::C_CH_BunnyHop(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_bhop_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_bhop_key_use"), XS("32"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_bhop_autoctrl"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_bNeedToJump = false;
  m_iPerformSleepTime = 1000;
  m_bIsCheatInitialized = false;
}

C_CH_BunnyHop::~C_CH_BunnyHop()
{
  C_CVarMgr::UnRegConVar(XS("krx_bhop_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_bhop_key_use"));
  C_CVarMgr::UnRegConVar(XS("krx_bhop_autoctrl"));
}

void C_CH_BunnyHop::restoreChanges()
{
  if (!GetAsyncKeyState(VK_LCONTROL)) // not pressing duck-key in game
  {
    if (m_pPlayer->Team() == TEAM_SURV
        || (m_pPlayer->Team() == TEAM_INFECT
            && m_pPlayer->CurWeapID() != WEAPON_ID_HUNTER_CLAW))
    {
      //*pCMgr->m_piDuck_Status = ACTION_MINUS;
      g_pEngineClient->ExecCMD(XS("-duck"));
    }
  }
}

void C_CH_BunnyHop::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_bhop_enabled"))->GetInt() == 1 ? true : false;
  m_iKeyCheatUse = C_CVarMgr::FindVar(XS("krx_bhop_key_use"))->GetInt();
  m_bAutoCtrl = C_CVarMgr::FindVar(XS("krx_bhop_autoctrl"))->GetInt() == 1 ? true : false;
}

void C_CH_BunnyHop::perform()
{
  if (IS_EXEC_ALLOWED)
  {
    if (pCmd->buttons & IN_JUMP)
    {
      float flForwardVelocity = m_pPlayer->Velocity(0);
      float flSideVelocity = m_pPlayer->Velocity(1);
      float flFallVelocity = m_pPlayer->Velocity(2);

      if (flFallVelocity > 0.0f)
      {
        if (m_bAutoCtrl)
        {
          pCmd->buttons &= ~IN_DUCK;
        }
      }
      if (flFallVelocity < 0.0f)
      {
        pCmd->buttons &= ~IN_JUMP;

        if ((m_pPlayer->Team() == TEAM_SURV && Utils::Get2dSummaryVelocity(flForwardVelocity, flSideVelocity) > 220.0f)
            || (m_pPlayer->Team() == TEAM_INFECT && Utils::Get2dSummaryVelocity(flForwardVelocity, flSideVelocity) > 150.0f))
        {
          if (m_bAutoCtrl)
          {
            pCmd->buttons |= IN_DUCK;
          }
        }
      }
      if (flFallVelocity == 0.0f)
      {
        C_CheatMgr::Instance->SendPacketStatus(true);
        if (m_bAutoCtrl)
        {
          pCmd->buttons &= ~IN_DUCK;
        }
      }
    }
  }
}