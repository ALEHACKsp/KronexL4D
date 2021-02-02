#include "KronexMain.h"

C_CH_NoRecoil::C_CH_NoRecoil(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_norecoil_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_pRecoilFn = Utils::FindPattern(
    Modules::Client, XS("D9 07 D8 86 6C 0F 00 00 D9 1F D9 86 70 0F 00 00 D8 47 04 D9 5F 04 D9 86 74 0F 00 00 D8 47 08 D9 5F 08"), XS("m_pRecoilFn"), 2);
  pPMgr->RegPatch(m_pRecoilFn, XS("90 90 90 90 90 90"), XS("m_pRecoilFn"));

  m_iPerformSleepTime = 1000;
  m_bIsCheatInitialized = true;
}

C_CH_NoRecoil::~C_CH_NoRecoil()
{
  C_CVarMgr::UnRegConVar(XS("krx_norecoil_enabled"));
}

void C_CH_NoRecoil::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_norecoil_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_NoRecoil::perform()
{
  pPMgr->ApplyPatch(XS("m_pRecoilFn"));
}

void C_CH_NoRecoil::restoreChanges()
{
  pPMgr->RestorePatch(XS("m_pRecoilFn"));
}

