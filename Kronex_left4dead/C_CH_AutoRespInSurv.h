#pragma once

class C_CH_AutoRespInSurv : public C_Cheat
{
public:
  C_CH_AutoRespInSurv(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_AutoRespInSurv();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();
};

