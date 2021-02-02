#pragma once

#include "C_Cheat.h"

class C_CH_BunnyHop : public C_Cheat
{
public:
	C_CH_BunnyHop(C_CheatManager* cheatManager, string cheatName);
	virtual ~C_CH_BunnyHop(VOID);

	virtual VOID perform(VOID);
	virtual VOID restoreChanges(VOID);
	virtual VOID statusSwitched(VOID);

private:
  BOOL m_bNeedToJump;
};

