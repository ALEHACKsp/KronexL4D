#pragma once

#include "C_Cheat.h"

class C_CH_VisualHacks : public C_Cheat
{
public:
	C_CH_VisualHacks(C_CheatManager* cheatManager, string cheatName);
	virtual ~C_CH_VisualHacks(VOID);

	virtual VOID perform(VOID);
	virtual VOID restoreChanges(VOID);
	virtual VOID statusSwitched(VOID);

private:
	PINT m_piFullBright;
	PINT m_piNoFog_1;
	PINT m_piNoFog_2;
  PINT m_piRenderWater;
  PINT m_piWitchBrightNess;
  PINT m_piWitchColor_r;
  PINT m_piWitchColor_g;
  PINT m_piWitchColor_b;

  PFLOAT m_pfWitchCone;
  PFLOAT m_pfWitchLightRadius;
};

