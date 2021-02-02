#include "KronexMain.h"

C_CH_Ceiling::C_CH_Ceiling(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_ceiling_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_ceiling_key_use"), XS("20"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_ceiling_clickpause"), XS("50"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_iLastClickTimer = clock();

  m_pAngleControllerFn = Utils::FindPattern(
    Modules::Engine, XS("D9 80 A4 4A 00 00 8B 4C 24 08 05 A4 4A 00 00 D9 19"), XS("m_pAngleControllerFn"), 0);
  pPMgr->RegPatch(m_pAngleControllerFn, XS("8B 4C 24 08 05 A4 4A 00 00 D9 EB D8 C0 D8 C0 D9 19"), XS("m_pAngleControllerFn"));

  m_iPerformSleepTime = 5;
  m_bIsCeilingNow = false;
  m_bIsCheatInitialized = true;
}

C_CH_Ceiling::~C_CH_Ceiling()
{
  C_CVarMgr::UnRegConVar(XS("krx_ceiling_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_ceiling_key_use"));
  C_CVarMgr::UnRegConVar(XS("krx_ceiling_clickpause"));
}

void C_CH_Ceiling::restoreChanges()
{
  pPMgr->RestorePatch(XS("m_pAngleControllerFn"));
}

void C_CH_Ceiling::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_ceiling_enabled"))->GetInt() == 1 ? true : false;
  m_iKeyCheatUse = C_CVarMgr::FindVar(XS("krx_ceiling_key_use"))->GetInt();
  m_iClickPause = C_CVarMgr::FindVar(XS("krx_ceiling_clickpause"))->GetInt();
}

void C_CH_Ceiling::perform()
{
  if (IS_EXEC_ALLOWED)
  {
    if (GetAsyncKeyState(m_iKeyCheatUse))
    {
      if (m_pPlayer->Team() == TEAM_INFECT
          && m_pPlayer->CharType() == CHARACTER_TYPE_HUNTER
          && m_pPlayer->IsAlive())
      {
        if (!m_bIsCeilingNow)
        {
          pPMgr->ApplyPatch(XS("m_pAngleControllerFn"));
          m_bIsCeilingNow = true;
        }
        if (clock() - m_iLastClickTimer > m_iClickPause)
        {
          //*pCMgr->m_piAttack_Status = ACTION_DO;
          g_pEngineClient->ExecCMD(XS("+attack; wait 100; -attack"));
          //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
          m_iLastClickTimer = clock();
        }
      }
    }
    else
    {
      if (m_bIsCeilingNow)
      {
        restoreChanges();
        m_bIsCeilingNow = false;
      }
    }
  }
}
