#pragma once

#include "C_Cheat.h"

class C_CH_Ceiling : public C_Cheat
{
public:
  C_CH_Ceiling(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_Ceiling(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

private:
  PCHAR m_pbMouseOriginBytes;
  PCHAR m_pbMouseHackBytes;

  DWORD m_dwAngleControllerFn;
  DWORD m_dwAngleControllerFnOldProtect;

  INT m_iLastClickTimer;
  BOOL m_bIsCeilingNow;
};

