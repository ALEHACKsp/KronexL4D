#pragma once

class C_CH_Aimbot : public C_Cheat
{
public:
	C_CH_Aimbot(C_CheatMgr* cheatManager, string cheatName);
	virtual ~C_CH_Aimbot();

	virtual void perform();
	virtual void restoreChanges();
  virtual void update();

  int GetBestBone(C_Player* target);
	int findTargets();
	bool sortTargets();
  bool IsAbleToShoot();
  bool AutoWall(C_Player* target, int bone);
  void FixSpread(C_Player* target);

  static bool SortByHealthFunc(C_Player* player1, C_Player* player2);
  static bool SortByDistanceFunc(C_Player* player1, C_Player* player2);
  static bool SortByAngleFunc(C_Player* player1, C_Player* player2);
  static DWORD actionAfterShoot(LPVOID SleepTime);

	vector<C_Player*> TargetList;
//private:

  bool m_bSilent;

  string m_sActionAfterShoot;
  bool m_bShooted;
  bool m_bAutoShoot;

  //float m_mflOldAngles[2];
  float m_flShotgunsSmooth;

  float m_flFOV;
  float m_flRange;

  int m_iSortType;
  int m_iBoneNumber;
  int m_iActionAfterShootTimer;
  
  //int m_iSilentSleep;
  int m_iTimeLastShoot;

  int m_iMyWeapon;

  int m_iSilentDelta1;
  int m_iSilentDelta2;
};

