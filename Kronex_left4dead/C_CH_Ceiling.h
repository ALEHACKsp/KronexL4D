#pragma once

class C_CH_Ceiling : public C_Cheat
{
public:
  C_CH_Ceiling(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_Ceiling();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

private:
  void* m_pAngleControllerFn;

  int m_iClickPause;
  int m_iLastClickTimer;
  bool m_bIsCeilingNow;
};

