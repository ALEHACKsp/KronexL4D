#pragma once

class C_CH_Radar : public C_Cheat
{
public:
  C_CH_Radar(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_Radar();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

  int findTargets();

  Color GetColor(C_Player* target);

  vector<C_Player*> TargetList;

  int m_iColor_Smoker_Ghost_R;
  int m_iColor_Smoker_Ghost_G;
  int m_iColor_Smoker_Ghost_B;
  int m_iColor_Smoker_Spawned_R;
  int m_iColor_Smoker_Spawned_G;
  int m_iColor_Smoker_Spawned_B;
  int m_iColor_Boomer_Ghost_R;
  int m_iColor_Boomer_Ghost_G;
  int m_iColor_Boomer_Ghost_B;
  int m_iColor_Boomer_Spawned_R;
  int m_iColor_Boomer_Spawned_G;
  int m_iColor_Boomer_Spawned_B;
  int m_iColor_Hunter_Ghost_R;
  int m_iColor_Hunter_Ghost_G;
  int m_iColor_Hunter_Ghost_B;
  int m_iColor_Hunter_Spawned_R;
  int m_iColor_Hunter_Spawned_G;
  int m_iColor_Hunter_Spawned_B;
  int m_iColor_Tank_Ghost_R;
  int m_iColor_Tank_Ghost_G;
  int m_iColor_Tank_Ghost_B;
  int m_iColor_Tank_Spawned_R;
  int m_iColor_Tank_Spawned_G;
  int m_iColor_Tank_Spawned_B;

  int m_iPos_X;
  int m_iPos_Y;
  int m_iDrawRadius;
  float m_flRange;
  int m_iSegments;

  int m_iPointSize;
  int m_iPointSegments;

  bool m_bDrawFovLines;
  bool m_bDrawFovBackGround;
};

