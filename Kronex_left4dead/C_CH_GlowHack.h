//#pragma once
//
//class C_CH_GlowHack : public C_Cheat
//{
//public:
//  C_CH_GlowHack(C_CheatMgr* cheatManager, string cheatName);
//  virtual ~C_CH_GlowHack();
//
//  virtual void perform();
//  virtual void restoreChanges();
//  virtual void update();
//
//private:
//  void* m_pDistanceFn;
//
//  string m_sDistanceFnOrigin;
//  string m_sDistanceFnHack;
//
//};



#pragma once

class C_CH_GlowHack : public C_Cheat
{
public:
	C_CH_GlowHack(C_CheatMgr* cheatManager, string cheatName);
	virtual ~C_CH_GlowHack();

	virtual void perform();
	virtual void restoreChanges();
  virtual void update();

private:
  void* m_pGlowHackFn;

  void* m_pDistanceFn;

  string m_sGlowHackOrigin;
  string m_sGlowHackSurv;
  string m_sGlowHackInfect;
  string m_sGlowHackSpec;
};