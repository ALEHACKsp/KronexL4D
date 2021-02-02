#pragma once

class C_CH_ESP : public C_Cheat
{
public:
  C_CH_ESP(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_ESP();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

  int findTargets();

  bool PlayerBoneToScreen(C_Player* pPlayer, int boneID);

  Color GetColor(C_Player* target);

//private:
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

  int m_iTextColor_R;
  int m_iTextColor_G;
  int m_iTextColor_B;

  bool m_bDrawESPBox;
  int m_iBoxThickness;

  bool m_bDrawSkeleton;
  int m_iSkeletonThickness;

  bool m_bDrawSnapLine;
  int m_iSnapLineThickness;

  bool m_bDrawHealth;
  bool m_bDrawHealthVisual;
  bool m_bDrawNickName;
  bool m_bDrawTankFrustration;

  int m_iScreen_X;
  int m_iScreen_Y;

  int m_iDrawStyle;
};