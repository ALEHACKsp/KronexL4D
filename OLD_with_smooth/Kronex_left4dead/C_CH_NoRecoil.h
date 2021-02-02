#pragma once

#include "C_Cheat.h"

class C_CH_NoRecoil : public C_Cheat
{
public:
  C_CH_NoRecoil(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_NoRecoil(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

private:
  DWORD m_dwRecoilFn;
  DWORD m_dwRecoiFnOldProtect;

  PCHAR m_pbRecoilOriginBytes;
  PCHAR m_pbRecoilHackBytes;

};

