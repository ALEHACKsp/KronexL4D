#pragma once

class C_CH_MaterialHack : public C_Cheat
{
public:
  C_CH_MaterialHack(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_MaterialHack();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

private:
  IMaterial* pWitchMat;
};

