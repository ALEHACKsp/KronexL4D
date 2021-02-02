#pragma once

#include "C_Cheat.h"

class C_CH_CameraHack : public C_Cheat
{
public:
  C_CH_CameraHack(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_CameraHack(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

private:
  //PINT m_piThirdPersonStatus;
  //PINT m_piThirdPersonType;
  //PFLOAT m_pfThirdPersonDistance;

  PFLOAT m_pfCameraPos;
};

