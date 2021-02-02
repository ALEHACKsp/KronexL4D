#pragma once

class C_Player;

#include <vector>

#include "C_Cheat.h"
#include "C_Player.h"

class C_CH_Aimbot : public C_Cheat
{
public:
	C_CH_Aimbot(C_CheatManager* cheatManager, string cheatName);
	virtual ~C_CH_Aimbot(VOID);

	virtual VOID perform(VOID);
	virtual VOID restoreChanges(VOID);
	virtual VOID statusSwitched(VOID);

	INT findTargets(VOID);
	BOOL sortTargets(TargetSortTypes sortType);

  static BOOL SortByHealthFunc(C_Player* player1, C_Player* player2);
  static BOOL SortByDistanceFunc(C_Player* player1, C_Player* player2);
  static BOOL SortByAngleFunc(C_Player* player1, C_Player* player2);
  static DWORD actionAfterShoot(LPVOID SleepTime);

private:
	vector<C_Player*> TargetList;

  C_Player* TargetN1;
  C_Player* CapturedTarget;

  AngleCalculateTypes m_CalculateType;

	BOOL m_bShootedOnce;
  BOOL m_bCapturedOnce;
  BOOL m_bActionAfterShoot;
  BOOL m_bSilentMode;

  FLOAT m_mflOldAngles[2];

  FLOAT m_flFOV;
  FLOAT m_flRange;
  FLOAT m_flShotgunsSmooth;
  FLOAT m_flAutogunsSmooth;
  FLOAT m_flOldMouseSensitivity;

  INT m_iTimeSinceLastShoot;
  INT m_iBoneNumber;
  INT m_iTargetingTime;
  INT m_iActionAfterShootTimer;
};

