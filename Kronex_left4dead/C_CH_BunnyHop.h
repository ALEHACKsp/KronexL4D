#pragma once

class C_CH_BunnyHop : public C_Cheat
{
public:
	C_CH_BunnyHop(C_CheatMgr* cheatManager, string cheatName);
	virtual ~C_CH_BunnyHop();

	virtual void perform();
	virtual void restoreChanges();
  virtual void update();

private:
  bool m_bNeedToJump;
  bool m_bAutoCtrl;
};

