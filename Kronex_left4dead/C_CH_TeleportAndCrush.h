#pragma once

class C_CH_TeleportAndCrush : public C_Cheat
{
public:
  C_CH_TeleportAndCrush(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_TeleportAndCrush();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();
};

