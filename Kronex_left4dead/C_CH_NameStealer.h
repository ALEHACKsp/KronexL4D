#pragma once

class C_CH_NameStealer : public C_Cheat
{
public:
  C_CH_NameStealer(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_NameStealer();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

private:
  int m_iOldUserID;
  pinfo_s m_pInfo;
};

