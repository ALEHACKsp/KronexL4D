#include "C_CH_CameraHack.h"

C_CH_CameraHack::C_CH_CameraHack(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  //m_piThirdPersonStatus = (PINT)(m_pCManager->m_dwClientDll + 0x5A3DB0); // [0/256]
  //m_piThirdPersonType = (PINT)(m_pCManager->m_dwClientDll + 0x56C9B8); // [0/1]
  //m_pfThirdPersonDistance = (PFLOAT)(m_pCManager->m_dwClientDll + 0x56C69C); // min 30.0f
  m_pfCameraPos = (PFLOAT)(m_pCManager->m_dwClientDll + 0x5B23F4);

  m_iPerformSleepTime = 1000;
  m_iKeyCheatSwitchStatus = VK_NUMPAD3;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_CameraHack::~C_CH_CameraHack(VOID)
{

}

VOID C_CH_CameraHack::perform(VOID)
{

}

VOID C_CH_CameraHack::restoreChanges(VOID)
{
  //*m_pCManager->m_piSvCheats = 0;
  //*m_piThirdPersonStatus = 0;
  //*m_piThirdPersonType = 0;
  //*m_pfThirdPersonDistance = 30.0f;
  *m_pfCameraPos = 0.0f;
}

VOID C_CH_CameraHack::statusSwitched(VOID)
{
  if (!m_bIsCheatEnabled)
  {
    //*m_pCManager->m_piSvCheats = 1;
    //*m_piThirdPersonStatus = 256;
    //*m_piThirdPersonType = 0;
    //*m_pfThirdPersonDistance = 100.0f;
    *m_pfCameraPos = -100.0f;
  }
  else
  {
    restoreChanges();
  }
}
