#include <algorithm>    // std::sort
#include <cmath>

#include "C_CH_Aimbot.h"
#include "C_CH_FakeLag.h"

C_CH_Aimbot::C_CH_Aimbot(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_iPerformSleepTime = 2;
  m_iKeyCheatUse = VK_SHIFT;
  m_iKeyCheatSwitchStatus = VK_NUMPAD1;
  m_CalculateType = CalculateBySkin;
  m_flFOV = 40.0f;
  m_flRange = 10000.0f;
  m_flShotgunsSmooth = 50.0f; // 50 // if smooth 0 -> silent activated
  m_flAutogunsSmooth = 3.0f; // min[1.0f] // 3
  m_iBoneNumber = 11;
  m_iTargetingTime = 40;
  m_iActionAfterShootTimer = 65;
  m_bActionAfterShoot = FALSE;
  m_bSilentMode = TRUE;

  TargetN1 = 0;
  CapturedTarget = 0;
  m_iTimeSinceLastShoot = 0;
  m_flOldMouseSensitivity = 0.0f;
  m_bShootedOnce = FALSE;
  m_bCapturedOnce = FALSE;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_Aimbot::~C_CH_Aimbot(VOID)
{

}

INT C_CH_Aimbot::findTargets(VOID)
{
	TargetList.clear();
  if (!(m_pMyPlayer->Team() == TeamSurv) || !m_pMyPlayer->IsAlive() || !m_pMyPlayer->IsSpawned()) return 0;

	int entitiesCount = m_pEManager->EntityList.size();

	for (int i = 0; i < entitiesCount; i++)
	{
    C_Player *tempPlayer = m_pEManager->EntityList[i];

    if (tempPlayer->Team() == TeamInfect
			  && tempPlayer->IsAlive()
			  && tempPlayer->IsSpawned())
		{
			tempPlayer->CalculateAngleTo(m_pMyPlayer, m_CalculateType, m_iBoneNumber);
      TargetList.push_back(tempPlayer);
		}
	}
	return TargetList.size();
}

BOOL C_CH_Aimbot::SortByHealthFunc(C_Player* player1, C_Player* player2)
{
	return (player1->Health() < player2->Health());
}

BOOL C_CH_Aimbot::SortByDistanceFunc(C_Player* player1, C_Player* player2)
{
  C_Player* myPlayer = C_CH_Aimbot::Instance->m_pMyPlayer;
	return (player1->DistanceTo(myPlayer) < player2->DistanceTo(myPlayer));
}

BOOL C_CH_Aimbot::SortByAngleFunc(C_Player* player1, C_Player* player2)
{
	FLOAT AngleDistance1 = StaticFunctions::GetAngleDistance(C_CH_Aimbot::Instance->m_pCManager->m_pfCrossHairController, player1->GetAngle());
	FLOAT AngleDistance2 = StaticFunctions::GetAngleDistance(C_CH_Aimbot::Instance->m_pCManager->m_pfCrossHairController, player2->GetAngle());

	return (AngleDistance1 < AngleDistance2);
}

BOOL C_CH_Aimbot::sortTargets(TargetSortTypes sortType)
{
  INT TargetsCount = TargetList.size();

  if (TargetsCount < 1)
    return FALSE;
  else if (TargetsCount == 1)
    return TRUE;
  else
  {
    switch (sortType)
    {
      case SortByAngle:
      {
        sort(TargetList.begin(), TargetList.end(), SortByAngleFunc);
        return TRUE;
      }
      case SortByHealth:
      {
        sort(TargetList.begin(), TargetList.end(), SortByHealthFunc);
        return TRUE;
      }
      case SortByDistance:
      {
        sort(TargetList.begin(), TargetList.end(), SortByDistanceFunc);
        return TRUE;
      }
      default:
      {
        return FALSE;
      }
    }
  }
}

VOID C_CH_Aimbot::perform(VOID)
{
	if (m_bIsCheatEnabled)
	{
    if (*m_pCManager->m_piIsPlayerOnServer == 1
        && *m_pCManager->m_pbIsChatClosed == 1
        && *m_pCManager->m_piIsESCPressed == 0
        && *m_pCManager->m_piIsOverlayRendered == 0)
    { 
      if (GetAsyncKeyState(m_iKeyCheatUse))
      {
        if (m_pMyPlayer->Team() == TeamSurv)
        {
          if (findTargets() > 0)
          {
            if (sortTargets(SortByAngle))
            {
              if (TargetN1 == 0) TargetN1 = TargetList[0];
              FLOAT distanceToMyPlayer = TargetN1->DistanceTo(m_pMyPlayer);
              WeaponIDs MyWeapon = m_pMyPlayer->CurWeapID();

              if (distanceToMyPlayer <= m_flRange)
              {
                TargetN1->CalculateAngleTo(m_pMyPlayer, CalculateBySkin, m_iBoneNumber); // для захвата по шкуре
                FLOAT angleToTarget = StaticFunctions::GetAngleDistance(m_pCManager->m_pfCrossHairController, TargetN1->GetAngle());

                if (angleToTarget <= m_flFOV || CapturedTarget != 0)
                {
                  if (m_CalculateType != CalculateBySkin) TargetN1->CalculateAngleTo(m_pMyPlayer, m_CalculateType, m_iBoneNumber); // вычисляем угол для стрельбы

                  if (MyWeapon == WeaponID_HUNTINGRIFLE
                      || MyWeapon == WeaponID_PISTOL
                      || MyWeapon == WeaponID_RIFLE
                      || MyWeapon == WeaponID_SMG)
                  {
                    if (m_bCapturedOnce == FALSE || CapturedTarget->IsAlive())
                    {
                      if (m_flOldMouseSensitivity == 0.0f)
                      {
                        m_flOldMouseSensitivity = *m_pCManager->m_pfMouseSensitivity; // сохраняем игровое управление мышью
                        *m_pCManager->m_pfMouseSensitivity = 0.0f; // отключаем игровое управление мышью
                      }

                      FLOAT ang_0 = TargetN1->GetAngle()[0];
                      FLOAT ang_1 = TargetN1->GetAngle()[1];
                      FLOAT cross_0 = m_pCManager->m_pfCrossHairController[0];
                      FLOAT cross_1 = m_pCManager->m_pfCrossHairController[1];

                      FLOAT difference_0 = ang_0 > cross_0 ? ang_0 - cross_0 : cross_0 - ang_0;
                      FLOAT difference_1 = ang_1 > cross_1 ? ang_1 - cross_1 : cross_1 - ang_1;

                      if (difference_0 >= 180.0f)
                      {
                        difference_0 = 360.0f - difference_0;
                        if (m_flAutogunsSmooth < 1.0f) m_flAutogunsSmooth = 1.0f;
                        m_pCManager->m_pfCrossHairController[0] += ang_0 < cross_0 ? difference_0 / m_flAutogunsSmooth : -(difference_0 / m_flAutogunsSmooth);
                      }
                      else m_pCManager->m_pfCrossHairController[0] += ang_0 > cross_0 ? difference_0 / m_flAutogunsSmooth : -(difference_0 / m_flAutogunsSmooth);

                      if (difference_1 >= 180.0f)
                      {
                        difference_1 = 360.0f - difference_1;
                        if (m_flAutogunsSmooth < 1.0f) m_flAutogunsSmooth = 1.0f;
                        m_pCManager->m_pfCrossHairController[1] += ang_1 < cross_1 ? difference_1 / m_flAutogunsSmooth : -(difference_1 / m_flAutogunsSmooth);
                      }
                      else m_pCManager->m_pfCrossHairController[1] += ang_1 > cross_1 ? difference_1 / m_flAutogunsSmooth : -(difference_1 / m_flAutogunsSmooth);

                      CapturedTarget = TargetN1;
                      m_bCapturedOnce = TRUE;

                      this_thread::sleep_for(chrono::nanoseconds(1000000)); // 1ms
                    }
                  }
                  else if (MyWeapon == WeaponID_PUMPSHOTGUN || MyWeapon == WeaponID_AUTOSHOTGUN)
                  {
                    if (m_bShootedOnce == FALSE)
                    {
                      if (m_flOldMouseSensitivity == 0.0f)
                      {
                        m_flOldMouseSensitivity = *m_pCManager->m_pfMouseSensitivity; // сохраняем игровое управление мышью
                        *m_pCManager->m_pfMouseSensitivity = 0.0f; // отключаем игровое управление мышью
                      }

                      if (m_flShotgunsSmooth > 0.0f && m_bSilentMode == FALSE)	// плавное перемещение курсора
                      {
                        FLOAT ang_0;
                        FLOAT ang_1;
                        FLOAT cross_0;
                        FLOAT cross_1;

                        FLOAT difference_0;
                        FLOAT difference_1;

                        for (FLOAT i = 0.0f; i < m_flShotgunsSmooth && TargetN1->IsAlive(); i++)
                        {
                          TargetN1->CalculateAngleTo(m_pMyPlayer, m_CalculateType, m_iBoneNumber);

                          ang_0 = TargetN1->GetAngle()[0];
                          ang_1 = TargetN1->GetAngle()[1];
                          cross_0 = m_pCManager->m_pfCrossHairController[0];
                          cross_1 = m_pCManager->m_pfCrossHairController[1];

                          difference_0 = ang_0 > cross_0 ? ang_0 - cross_0 : cross_0 - ang_0;
                          difference_1 = ang_1 > cross_1 ? ang_1 - cross_1 : cross_1 - ang_1;

                          if (difference_0 >= 180.0f)
                          {
                            difference_0 = 360.0f - difference_0;
                            m_pCManager->m_pfCrossHairController[0] += ang_0 < cross_0 ? difference_0 / (m_flShotgunsSmooth - i) : -(difference_0 / (m_flShotgunsSmooth - i));
                          }
                          else m_pCManager->m_pfCrossHairController[0] += ang_0 > cross_0 ? difference_0 / (m_flShotgunsSmooth - i) : -(difference_0 / (m_flShotgunsSmooth - i));

                          if (difference_1 >= 180.0f)
                          {
                            difference_1 = 360.0f - difference_1;
                            m_pCManager->m_pfCrossHairController[1] += ang_1 < cross_1 ? difference_1 / (m_flShotgunsSmooth - i) : -(difference_1 / (m_flShotgunsSmooth - i));
                          }
                          else m_pCManager->m_pfCrossHairController[1] += ang_1 > cross_1 ? difference_1 / (m_flShotgunsSmooth - i) : -(difference_1 / (m_flShotgunsSmooth - i));

                          if (i + 1.0f >= m_flShotgunsSmooth)
                          {
                            *m_pCManager->m_piAttack_Status = ActionPlus;
                            m_iTimeSinceLastShoot = clock();

                            do
                            {
                              m_pCManager->m_pfCrossHairController[0] = TargetN1->GetAngle()[0];
                              m_pCManager->m_pfCrossHairController[1] = TargetN1->GetAngle()[1];
                              TargetN1->CalculateAngleTo(m_pMyPlayer, m_CalculateType, m_iBoneNumber);
                            } while (clock() - m_iTimeSinceLastShoot < m_iTargetingTime && TargetN1->IsAlive());

                            break;
                          }

                          this_thread::sleep_for(chrono::nanoseconds(100)); // 0.0001ms
                        }
                      }
                      else // if smooth <= 0 or silentmode is true
                      {
                        if (m_bSilentMode)
                        {
                          if (C_CH_FakeLag::Instance != 0)
                          {
                            C_CH_FakeLag* fakeLagCheat = static_cast<C_CH_FakeLag*>(C_CH_FakeLag::Instance);
                            fakeLagCheat->SendPacketStatus(FALSE);

                            m_mflOldAngles[0] = m_pCManager->m_pfCrossHairController[0];
                            m_mflOldAngles[1] = m_pCManager->m_pfCrossHairController[1];
                          }
                        }

                        *m_pCManager->m_piAttack_Status = ActionPlus;
                        m_iTimeSinceLastShoot = clock();

                        do
                        {
                          m_pCManager->m_pfCrossHairController[0] = TargetN1->GetAngle()[0];
                          m_pCManager->m_pfCrossHairController[1] = TargetN1->GetAngle()[1];
                          TargetN1->CalculateAngleTo(m_pMyPlayer, m_CalculateType, m_iBoneNumber);
                          *m_pCManager->m_piAttack_Status = ActionPlus;
                        } while (clock() - m_iTimeSinceLastShoot < m_iTargetingTime && TargetN1->IsAlive());

                        if (m_bSilentMode)
                        {
                          m_iTimeSinceLastShoot = clock();

                          do
                          {
                            m_pCManager->m_pfCrossHairController[0] = m_mflOldAngles[0];
                            m_pCManager->m_pfCrossHairController[1] = m_mflOldAngles[1];
                          } while (clock() - m_iTimeSinceLastShoot < 2);

                          if (C_CH_FakeLag::Instance != 0)
                          {
                            C_CH_FakeLag* fakeLagCheat = static_cast<C_CH_FakeLag*>(C_CH_FakeLag::Instance);
                            fakeLagCheat->SendPacketStatus(TRUE);
                          }
                        }
                      }

                      if (m_bActionAfterShoot) // действие после выстрела
                      {
                        m_hThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)actionAfterShoot, &m_iActionAfterShootTimer, NULL, NULL);
                      }

                      m_bShootedOnce = TRUE;

                      if (m_flOldMouseSensitivity != 0.0f)
                      {
                        *m_pCManager->m_pfMouseSensitivity = m_flOldMouseSensitivity; // включаем игровое управление мышью
                        m_flOldMouseSensitivity = 0.0f;
                      }
                    }
                  }
                }
              }
            }
          }
          if (m_bCapturedOnce == TRUE && CapturedTarget->IsAlive() == FALSE)
          {
            if (m_flOldMouseSensitivity != 0.0f)
            {
              *m_pCManager->m_pfMouseSensitivity = m_flOldMouseSensitivity; // включаем игровое управление мышью
              m_flOldMouseSensitivity = 0.0f;
            }
          }
        }
      }
      else
      {
        if (TargetN1 != 0) TargetN1 = 0;
        if (CapturedTarget != 0) CapturedTarget = 0;
        if (m_bCapturedOnce == TRUE) m_bCapturedOnce = FALSE;
        if (m_flOldMouseSensitivity != 0.0f)
        {
          *m_pCManager->m_pfMouseSensitivity = m_flOldMouseSensitivity; // включаем игровое управление мышью
          m_flOldMouseSensitivity = 0.0f;
        }

        if (m_bShootedOnce == TRUE)
        {
          if (clock() - m_iTimeSinceLastShoot > m_flShotgunsSmooth)
          {
            *m_pCManager->m_piAttack_Status = ActionMinus;
            m_bShootedOnce = FALSE;
          }
        }
      }
    }
	}
}

DWORD C_CH_Aimbot::actionAfterShoot(LPVOID SleepTime)
{
  this_thread::sleep_for(chrono::milliseconds(*(PINT)SleepTime));

  mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);

  /*keybd_event(0x32, MapVirtualKeyEx(0x32, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
  this_thread::sleep_for(chrono::milliseconds(40));
  keybd_event(0x32, MapVirtualKeyEx(0x32, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
  this_thread::sleep_for(chrono::milliseconds(40));
  keybd_event(0x31, MapVirtualKeyEx(0x31, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
  this_thread::sleep_for(chrono::milliseconds(40));
  keybd_event(0x31, MapVirtualKeyEx(0x31, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);*/

  ExitThread(0);
}

VOID C_CH_Aimbot::restoreChanges(VOID)
{

}

VOID C_CH_Aimbot::statusSwitched(VOID)
{

}
