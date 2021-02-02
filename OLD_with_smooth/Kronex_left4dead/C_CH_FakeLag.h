#pragma once

#include "C_Cheat.h"

class C_CH_FakeLag : public C_Cheat
{
public:
  C_CH_FakeLag(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_FakeLag(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

  static VOID SendPacketStatus(BOOL bSendPacketStatus);

  PCHAR m_pbSendPacketInitializeValue_TRUE;
  PCHAR m_pbSendPacketInitializeValue_FALSE;

  DWORD m_dwSendPacketInitializeValue;
  DWORD m_dwSendPacketInitializeValue_OldProtect;
};

