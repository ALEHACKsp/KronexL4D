#include "KronexMain.h"

//C_CH_GlowHack::C_CH_GlowHack(C_CheatMgr* cheatManager, string cheatName)
//  : C_Cheat(cheatManager, cheatName)
//{
//  C_CVarMgr::RegConVar(XS("krx_glowhack_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
//
//  m_sDistanceFnOrigin = XS("D8");
//  m_sDistanceFnHack = XS("D9");
//
//  m_pDistanceFn = Utils::FindPattern(
//    Modules::Client, XS("D8 D1 DF E0 F6 C4 05 7A 04 DD D9 EB 02 DD D8 D8 55 00 DF E0 F6 C4 05 7A 67"), XS("m_pDistanceFn"), 0xE);
//  pPMgr->RegPatch(m_pDistanceFn, m_sDistanceFnHack, XS("m_pDistanceFn"));
//
//  m_iPerformSleepTime = 1000;
//  m_bIsCheatEnabled = true;
//  m_bIsCheatInitialized = true;
//}
//
//C_CH_GlowHack::~C_CH_GlowHack()
//{
//  C_CVarMgr::UnRegConVar(XS("krx_glowhack_enabled"));
//}
//
//void C_CH_GlowHack::update()
//{
//  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_glowhack_enabled"))->GetInt() == 1 ? true : false;
//}
//
//void C_CH_GlowHack::restoreChanges()
//{
//  pPMgr->RestorePatch(XS("m_pDistanceFn"));
//
//  if (IS_EXEC_ALLOWED)
//  {
//    int entitiesCount = pEMgr->EntityList.size();
//    m_pPlayer->SetTeam(m_pPlayer->Team());
//
//    for (int i = 0; i < entitiesCount; i++)
//    {
//      C_Player* tempTarget = pEMgr->EntityList[i];
//
//      tempTarget->SetTeam(tempTarget->Team());
//    }
//  }
//}
//
//void C_CH_GlowHack::perform()
//{
//  if (IS_EXEC_ALLOWED)
//  {
//    pPMgr->ApplyPatch(XS("m_pDistanceFn"));
//
//    if (*pCMgr->m_piIsPlayerOnServer == 1)
//    {
//      int entitiesCount = pEMgr->EntityList.size();
//
//      for (int i = 0; i < entitiesCount; i++)
//      {
//        C_Player* tempPlayer = pEMgr->EntityList[i];
//
//        if (m_pPlayer->Team() == TEAM_SURV
//            && tempPlayer->Team() == TEAM_INFECT)
//        {
//          tempPlayer->SetTeam(TEAM_SURV);
//        }
//      }
//    }
//  }
//}







C_CH_GlowHack::C_CH_GlowHack(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_glowhack_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_sGlowHackOrigin = XS("8B 81 BC 00 00 00");
  m_sGlowHackSpec = XS("B8 01 00 00 00 90");
  m_sGlowHackSurv = XS("B8 02 00 00 00 90");
  m_sGlowHackInfect = XS("B8 03 00 00 00 90");

  m_pGlowHackFn = Utils::FindPattern(
    Modules::Client, XS("8B 01 8B 90 30 01 00 00 FF D2 33 C9 83 F8 02 0F 94 C1 8A C1 C3 CC CC CC CC CC CC CC CC CC CC CC 8B 81 BC 00 00 00 C3"), XS("m_pGlowHackFn"), 32);
  pPMgr->RegPatch(m_pGlowHackFn, m_sGlowHackOrigin, XS("m_pGlowHackFn"));

  m_pDistanceFn = Utils::FindPattern(
    Modules::Client, XS("D8 D1 DF E0 F6 C4 05 7A 04 DD D9 EB 02 DD D8 D8 55 00 DF E0 F6 C4 05 7A 67"), XS("m_pDistanceFn"), 14);
  pPMgr->RegPatch(m_pDistanceFn, XS("D9"), XS("m_pDistanceFn"));

  m_iPerformSleepTime = 1000;
  m_bIsCheatInitialized = true;
}

C_CH_GlowHack::~C_CH_GlowHack()
{
  C_CVarMgr::UnRegConVar(XS("krx_glowhack_enabled"));
}

void C_CH_GlowHack::restoreChanges()
{
  pPMgr->RestorePatch(XS("m_pGlowHackFn"));
  pPMgr->RestorePatch(XS("m_pDistanceFn"));
}

void C_CH_GlowHack::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_glowhack_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_GlowHack::perform()
{
  //if (*pCMgr->m_piIsPlayerOnServer == 1)
  if (IS_EXEC_ALLOWED)
  {
    pPMgr->RestorePatch(XS("m_pGlowHackFn"));

    if (m_pPlayer->Team() == TEAM_SURV)
    {
      pPMgr->GetPatch(XS("m_pGlowHackFn"))->SetNewBytes(m_sGlowHackSurv);
    }
    else if (m_pPlayer->Team() == TEAM_SPEC)
    {
      pPMgr->GetPatch(XS("m_pGlowHackFn"))->SetNewBytes(m_sGlowHackInfect);
    }
    else if (m_pPlayer->Team() == TEAM_INFECT)
    {
      pPMgr->GetPatch(XS("m_pGlowHackFn"))->SetNewBytes(m_sGlowHackOrigin);
    }

    pPMgr->ApplyPatch(XS("m_pGlowHackFn"));
    pPMgr->ApplyPatch(XS("m_pDistanceFn"));
  }
}