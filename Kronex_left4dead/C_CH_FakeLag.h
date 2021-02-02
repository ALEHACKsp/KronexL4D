#pragma once

class C_CH_FakeLag : public C_Cheat
{
public:
  C_CH_FakeLag(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_FakeLag();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

private:
  bool m_bIsLagging;
};

