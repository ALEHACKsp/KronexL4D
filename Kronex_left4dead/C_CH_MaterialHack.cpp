#include "KronexMain.h"

C_CH_MaterialHack::C_CH_MaterialHack(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  //C_CVarMgr::RegConVar(XS("krx_fakelag_enabled"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  pWitchMat = NULL;
  pWitchMat = g_pMaterialSystem->FindMaterial(XS("\\models\\infected\\witch\\witch"), XS(TEXTURE_GROUP_MODEL));

  m_iPerformSleepTime = 500;
  m_bIsCheatEnabled = true;
  m_bIsCheatInitialized = false;
}

C_CH_MaterialHack::~C_CH_MaterialHack()
{
  //C_CVarMgr::UnRegConVar(XS("krx_fakelag_enabled"));
}

void C_CH_MaterialHack::update()
{
  //m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_fakelag_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_MaterialHack::perform()
{
  if (IS_EXEC_ALLOWED)
  {    
    //pWitchMat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
    if (pWitchMat)
    {
      cout << "here!" << endl;
      pWitchMat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
    }
  }
}

void C_CH_MaterialHack::restoreChanges()
{
  pWitchMat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
}
