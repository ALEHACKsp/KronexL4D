#include "C_CH_VisualHacks.h"

C_CH_VisualHacks::C_CH_VisualHacks(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  //m_iKeyCheatSwitchStatus = VK_F6;

	m_piFullBright = (PINT)(m_pCManager->m_dwMaterialSystemDll + 0xEF668);
	m_piNoFog_1 = (PINT)(m_pCManager->m_dwClientDll + 0x597268);
	m_piNoFog_2 = (PINT)(m_pCManager->m_dwClientDll + 0x597388);
  m_piRenderWater = (PINT)(m_pCManager->m_dwClientDll + 0x5977C0);
  m_piWitchBrightNess = (PINT)(m_pCManager->m_dwClientDll + 0x5BEE78);
  m_piWitchColor_r = (PINT)(m_pCManager->m_dwClientDll + 0x5BEFE0);
  m_piWitchColor_g = (PINT)(m_pCManager->m_dwClientDll + 0x5BF028);
  m_piWitchColor_b = (PINT)(m_pCManager->m_dwClientDll + 0x5BF070);
  m_pfWitchCone = (PFLOAT)(m_pCManager->m_dwClientDll + 0x5BEF94);
  m_pfWitchLightRadius = (PFLOAT)(m_pCManager->m_dwClientDll + 0x5BEEBC);

	m_iPerformSleepTime = 1000;
  m_bIsCheatEnabled = TRUE;
  statusSwitched();
  m_bIsCheatInitialized = TRUE;
}

C_CH_VisualHacks::~C_CH_VisualHacks(VOID)
{

}

VOID C_CH_VisualHacks::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    srand(clock());

    int colors[][3] = {
      { 255, 0, 0 },
      { 255, 255, 0 },
      { 255, 0, 255 },
      { 0, 255, 0 },
      { 0, 255, 255 },
      { 0, 0, 255 },
    };

    int index = rand() % 6;
    *m_piWitchColor_r = colors[index][0];
    *m_piWitchColor_g = colors[index][1];
    *m_piWitchColor_b = colors[index][2];

    this_thread::sleep_for(chrono::milliseconds(1000));
    *m_piWitchColor_r = 0;
    *m_piWitchColor_g = 0;
    *m_piWitchColor_b = 0;
  }
}

VOID C_CH_VisualHacks::restoreChanges(VOID)
{
  //*m_piFullBright = 0;
  *m_piNoFog_1 = 0;
  *m_piNoFog_2 = 1;
  *m_piRenderWater = 1;
  *m_piWitchBrightNess = 5;
  *m_pfWitchLightRadius = 60.0f;
  *m_pfWitchCone = 45.0f;
  *m_piWitchColor_r = 255;
  *m_piWitchColor_g = 0;
  *m_piWitchColor_b = 0;
}

VOID C_CH_VisualHacks::statusSwitched(VOID)
{
  if (m_bIsCheatEnabled)
  {
    //*m_piFullBright = 1;
    *m_piNoFog_1 = 1;
    *m_piNoFog_2 = 0;
    *m_piRenderWater = 0;
    *m_piWitchBrightNess = 20;
    *m_pfWitchCone = 0.0f;
    *m_pfWitchLightRadius = 200.0f;
  }
  else
  {
    restoreChanges();
  }
}