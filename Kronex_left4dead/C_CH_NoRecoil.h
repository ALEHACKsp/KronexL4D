#pragma once

class C_CH_NoRecoil : public C_Cheat
{
public:
  C_CH_NoRecoil(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_NoRecoil();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

private:
  void* m_pRecoilFn;
  DWORD m_dwRecoiFnOldProtect;

  char* m_pbRecoilOriginBytes;
  char* m_pbRecoilHackBytes;

};

