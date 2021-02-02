#include "KronexMain.h"

C_CH_NameStealer::C_CH_NameStealer(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_namestealer_enabled"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_iOldUserID = 1;

  m_iPerformSleepTime = 10000;
  m_bIsCheatInitialized = true;
}

C_CH_NameStealer::~C_CH_NameStealer()
{
  C_CVarMgr::UnRegConVar(XS("krx_namestealer_enabled"));
}

void C_CH_NameStealer::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_namestealer_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_NameStealer::perform()
{
  char pname[128];
  char consoleCmd[256];

  do
  {
    g_pEngineClient->GetPlayerInfo(++m_iOldUserID, &m_pInfo);
    sprintf(pname, "%s", m_pInfo.name - 8);

    if (m_iOldUserID >= g_pEngineClient->GetMaxClients())
    {
      m_iOldUserID = 1;
      return;
    }
  } while (strlen(pname) < 1 || m_iOldUserID == g_pEngineClient->GetLocalPlayer());

  if (m_iOldUserID != g_pEngineClient->GetLocalPlayer() && strlen(pname) > 0)
  {
    sprintf(consoleCmd, "%s\"`%s\"", XS("setinfo name "), pname);
    g_pEngineClient->ExecCMD(consoleCmd);
  }
}

void C_CH_NameStealer::restoreChanges()
{

}
