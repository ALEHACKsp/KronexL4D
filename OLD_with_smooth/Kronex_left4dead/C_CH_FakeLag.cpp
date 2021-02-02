#include "C_CH_FakeLag.h"

C_CH_FakeLag::C_CH_FakeLag(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_pbSendPacketInitializeValue_TRUE = "\xC6\x44\x24\x07\x01\xFF\xD2\x84\xC0\x74\x12\x80\xBE\x5C\x4A\x00\x00\x00\x0F\x84\x15\x04\x00\x00\xC6\x44\x24\x07\x00\x8B\x4E\x10\x8B\x01\x8B\x50\x18\xFF\xD2\x84\xC0\x74\x0B";
  m_pbSendPacketInitializeValue_FALSE = "\xC6\x44\x24\x07\x00\xFF\xD2\x84\xC0\x74\x12\x80\xBE\x5C\x4A\x00\x00\x00\x0F\x84\x15\x04\x00\x00\xC6\x44\x24\x07\x00\x8B\x4E\x10\x8B\x01\x8B\x50\x18\xFF\xD2\x84\xC0\x74\x0B";
  m_dwSendPacketInitializeValue = m_pCManager->FindPattern(m_pCManager->m_dwEngineDll, 0x100000, m_pbSendPacketInitializeValue_TRUE, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  VirtualProtect((LPVOID)m_dwSendPacketInitializeValue, 43, PAGE_EXECUTE_READWRITE, &m_dwSendPacketInitializeValue_OldProtect);

  m_iPerformSleepTime = 1;
  m_iKeyCheatUse = 0x46; // F
  m_iKeyCheatSwitchStatus = VK_NUMPAD6;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_FakeLag::~C_CH_FakeLag(VOID)
{
  VirtualProtect((LPVOID)m_dwSendPacketInitializeValue, 43, m_dwSendPacketInitializeValue_OldProtect, NULL);
}

VOID C_CH_FakeLag::SendPacketStatus(BOOL bSendPacketStatus)
{
  C_CH_FakeLag* fakeLagCheat = static_cast<C_CH_FakeLag*>(C_CH_FakeLag::Instance);

  if (bSendPacketStatus)
  {
    memcpy((PVOID)fakeLagCheat->m_dwSendPacketInitializeValue, fakeLagCheat->m_pbSendPacketInitializeValue_TRUE, 43);
  }
  else
  {
    memcpy((PVOID)fakeLagCheat->m_dwSendPacketInitializeValue, fakeLagCheat->m_pbSendPacketInitializeValue_FALSE, 43);
  }
}

VOID C_CH_FakeLag::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    if (GetAsyncKeyState(m_iKeyCheatUse))
    {
      //*m_pCManager->m_pfPacketsLimiter = 1.0f/128.0f; // 19
      //*m_pCManager->m_pfCmdRate = 0.0f;
      //*m_pCManager->m_piCmdRate = 0;
      //*m_pCManager->m_pfUpdRate = 0.0f;
      //*m_pCManager->m_piUpdRate = 0;
      //*m_pCManager->m_piFlushEntityPacket = 10000; // For debugging. Force the engine to flush an entity packet. (уменьшается)
      //*m_pCManager->m_piIgnorePackets = 1; // Force client to ignore packets (for debugging).
      //*m_pCManager->m_pfNetBlockMsg = 1.0f; // Discards incoming message: <0|1|name>
      //*m_pCManager->m_piNetDropPackets = 10; // Drops next n packets on client (уменьшается)
      //*m_pCManager->m_piNetFakeJitter = 10000; // Jitter fakelag packet time (хз, ни на что не влияет)
      //*m_pCManager->m_pfNetFakelag = 1000.0f; // Lag all incoming network data (including loopback) by this many milliseconds.
      //*m_pCManager->m_pfNetFakeloss = 40.0f; // Simulate packet loss as a percentage (negative means drop 1/n packets) (+)

      SendPacketStatus(FALSE);
      this_thread::sleep_for(chrono::milliseconds(120));
      SendPacketStatus(TRUE);
      this_thread::sleep_for(chrono::milliseconds(16));
    }
  }
}

VOID C_CH_FakeLag::restoreChanges(VOID)
{
  //*m_pCManager->m_pfPacketsLimiter = 1.0f/100.0f;
  //*m_pCManager->m_pfCmdRate = 100.0f;
  //*m_pCManager->m_piCmdRate = 100;
  //*m_pCManager->m_pfUpdRate = 100.0f;
  //*m_pCManager->m_piUpdRate = 100;
  //*m_pCManager->m_piFlushEntityPacket = 0;
  //*m_pCManager->m_piIgnorePackets = 0;
  //*m_pCManager->m_pfNetBlockMsg = 0.0f;
  //*m_pCManager->m_piNetDropPackets = 0;
  //*m_pCManager->m_piNetFakeJitter = 0;
  //*m_pCManager->m_pfNetFakelag = 0.0f;
  //*m_pCManager->m_pfNetFakeloss = 0.0f;

  SendPacketStatus(TRUE);
}

VOID C_CH_FakeLag::statusSwitched(VOID)
{

}
