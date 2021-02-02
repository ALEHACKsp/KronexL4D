#pragma once

class C_CH_ConfigExecuter : public C_Cheat
{
public:
  C_CH_ConfigExecuter(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_ConfigExecuter();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

  void ReadConfigFile(const string &fileName);
};

