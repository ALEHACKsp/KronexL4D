#pragma once

#include "C_Cheat.h"

class C_CH_NoSpread : public C_Cheat
{
public:
  C_CH_NoSpread(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_NoSpread(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

private:
  DWORD m_dwSpreadFn1;
  DWORD m_dwSpreadFn2;
  DWORD m_dwSpreadFn3;
  DWORD m_dwSpreadFnOldProtect1;
  DWORD m_dwSpreadFnOldProtect2;
  DWORD m_dwSpreadFnOldProtect3;

  PCHAR m_pbSpreadOriginBytes1;
  PCHAR m_pbSpreadOriginBytes2;
  PCHAR m_pbSpreadOriginBytes3;
  PCHAR m_pbSpreadHackBytes1;
  PCHAR m_pbSpreadHackBytes2;
  PCHAR m_pbSpreadHackBytes3;
};

