#pragma once

#include "C_Cheat.h"

class C_CH_RespInSurv : public C_Cheat
{
public:
  C_CH_RespInSurv(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_RespInSurv(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);
};

