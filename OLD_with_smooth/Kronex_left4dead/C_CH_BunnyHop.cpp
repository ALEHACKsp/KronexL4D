#include <windows.h>

#include "C_CH_BunnyHop.h"
#include "C_CH_FakeLag.h"

C_CH_BunnyHop::C_CH_BunnyHop(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_iPerformSleepTime = 0;
  m_iKeyCheatUse = VK_SPACE;
  m_bNeedToJump = FALSE;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_BunnyHop::~C_CH_BunnyHop(VOID)
{

}

VOID C_CH_BunnyHop::restoreChanges(VOID)
{
	*m_pCManager->m_piJump_Status = ActionMinus;
}

VOID C_CH_BunnyHop::statusSwitched(VOID)
{
  *m_pCManager->m_piJump_Status = ActionMinus;
}

VOID C_CH_BunnyHop::perform(VOID)
{
	if (m_bIsCheatEnabled)
	{
    if (*m_pCManager->m_piIsPlayerOnServer == 1
        && *m_pCManager->m_pbIsChatClosed == 1
        && *m_pCManager->m_piIsESCPressed == 0
        && *m_pCManager->m_piIsOverlayRendered == 0)
    {
      FLOAT MyJumpVelocity = m_pMyPlayer->JumpVelocity();

      if (GetAsyncKeyState(m_iKeyCheatUse))
      {
        if (MyJumpVelocity == 0.0f) // on the floor
        {
          if (C_CH_FakeLag::Instance != 0)
          {
            C_CH_FakeLag* fakeLagCheat = static_cast<C_CH_FakeLag*>(C_CH_FakeLag::Instance);
            fakeLagCheat->SendPacketStatus(TRUE);
          }
          m_bNeedToJump = TRUE;
          *m_pCManager->m_piJump_Status = ActionPlus;

          if (m_pMyPlayer->Team() == TeamSurv
              || (m_pMyPlayer->Team() == TeamInfect && m_pMyPlayer->CurWeapID() != WeaponID_HUNTER_CLAW))
          {
            *m_pCManager->m_piDuck_Status = ActionMinus;
          }
        }
        else if (MyJumpVelocity < 0.0f) // falling
        {
          *m_pCManager->m_piJump_Status = ActionMinus;

          if (m_pMyPlayer->Team() == TeamSurv
              || (m_pMyPlayer->Team() == TeamInfect && m_pMyPlayer->CurWeapID() != WeaponID_HUNTER_CLAW))
          {
            *m_pCManager->m_piDuck_Status = ActionPlus;
          }
        }
        else if (MyJumpVelocity > 0.0f) // jumped
        {
          *m_pCManager->m_piJump_Status = ActionMinus;

          if (m_pMyPlayer->Team() == TeamSurv
              || (m_pMyPlayer->Team() == TeamInfect && m_pMyPlayer->CurWeapID() != WeaponID_HUNTER_CLAW))
          {
            *m_pCManager->m_piDuck_Status = ActionMinus;
          }
        }
      }
      else // not pressing bhop-key
      {
        if (MyJumpVelocity == 0.0f) // on the floor
        {
          if (m_bNeedToJump == TRUE)
          {
            *m_pCManager->m_piJump_Status = ActionMinus;
            m_bNeedToJump = FALSE;
          }
        }
        if (!GetAsyncKeyState(VK_LCONTROL)) // not pressing duck-key in game
        {
          if (m_pMyPlayer->Team() == TeamSurv
             || (m_pMyPlayer->Team() == TeamInfect && m_pMyPlayer->CurWeapID() != WeaponID_HUNTER_CLAW))
          {
            *m_pCManager->m_piDuck_Status = ActionMinus;
          }
        }
      }
    }
	}
}