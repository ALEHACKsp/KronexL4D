//#pragma once
//
//class C_Player;
//
//#include "C_Cheat.h"
//
//class C_CH_GlowHack : public C_Cheat
//{
//public:
//	C_CH_GlowHack(C_CheatManager* cheatManager, string cheatName);
//	virtual ~C_CH_GlowHack(VOID);
//
//	virtual VOID perform(VOID);
//	virtual VOID restoreChanges(VOID);
//	virtual VOID statusSwitched(VOID);
//
//private:
//  DWORD m_dwGlowHackFn;
//  DWORD m_dwGlowHackFnOldProtect;
//  DWORD m_dwDistanceFn;
//  DWORD m_dwDistanceFnOldProtect;
//
//  PCHAR m_pcGlowHackFnSingature;
//  PCHAR m_pcGlowHackOrigin;
//  PCHAR m_pcGlowHackSurv;
//  PCHAR m_pcGlowHackInfect;
//  PCHAR m_pcGlowHackSpec;
//
//  PCHAR m_pcDistanceFnSingature;
//  PCHAR m_pcDistanceFnOrigin;
//  PCHAR m_pcDistanceFnHack;
//
//};
//

#pragma once

class C_Player;

#include "C_Cheat.h"

class C_CH_GlowHack : public C_Cheat
{
public:
  C_CH_GlowHack(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_GlowHack(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

private:
  DWORD m_dwDistanceFn;
  DWORD m_dwDistanceFnOffset;
  DWORD m_dwDistanceFnOldProtect;

  PCHAR m_pcDistanceFnSingature;
  PCHAR m_pcDistanceFnOrigin;
  PCHAR m_pcDistanceFnHack;

};
