#pragma once

#include "C_Cheat.h"

#define COLOR_RED			    RGB(255, 0, 0)
#define COLOR_GREEN			  RGB(0, 255, 0)
#define COLOR_BLUE			  RGB(0, 0, 255)
#define COLOR_YELLOW		  RGB(255, 255, 0)
#define COLOR_PURPLE		  RGB(153, 0, 102)
#define COLOR_LIGHTPURPLE	RGB(153, 153, 255)
#define COLOR_LIGHTBLUE		RGB(0, 255, 255)
#define COLOR_ORANGE		  RGB(255, 127, 0)
#define COLOR_PINK			  RGB(255, 153, 153)
#define COLOR_BLACK			  RGB(0, 0, 0)
#define COLOR_WHITE			  RGB(255, 255, 255)
#define COLOR_GRAY			  RGB(204, 204, 204)

#define COLOR_TEXT			  RGB(0, 255, 0)
#define SnapLineCOLOR		  RGB(0, 0, 255)

class C_CH_ESP : public C_Cheat
{
public:
  C_CH_ESP(C_CheatManager* cheatManager, string cheatName);
  virtual ~C_CH_ESP(VOID);

  virtual VOID perform(VOID);
  virtual VOID restoreChanges(VOID);
  virtual VOID statusSwitched(VOID);

  static BOOL SortByHealthFunc(C_Player* player1, C_Player* player2);
  static BOOL SortByDistanceFunc(C_Player* player1, C_Player* player2);

  INT findTargets(VOID);
  BOOL sortTargets(TargetSortTypes sortType);

  VOID DrawESP(INT x, INT y, C_Player* target);
  VOID DrawLine(INT StartX, INT StartY, INT EndX, INT EndY, INT thickness, COLORREF CurrentColor);
  VOID DrawBorderBox(INT x, INT y, INT w, INT h, INT thickness, COLORREF CurrentColor);
  VOID DrawFilledRect(INT x, INT y, INT w, INT h, COLORREF CurrentColor);
  VOID DrawString(INT x, INT y, COLORREF color, CONST PCHAR text);
  BOOL WorldToScreen(PFLOAT from, PFLOAT to);

private:
  vector<C_Player*> TargetList;

  HWND hWnd;

  RECT m_Rect;
  HFONT m_Font;				//font we use to write text with
  COLORREF m_TextColor;

  INT m_iColor_Smoker_Ghost_R;
  INT m_iColor_Smoker_Ghost_G;
  INT m_iColor_Smoker_Ghost_B;
  INT m_iColor_Smoker_Spawned_R;
  INT m_iColor_Smoker_Spawned_G;
  INT m_iColor_Smoker_Spawned_B;
  INT m_iColor_Boomer_Ghost_R;
  INT m_iColor_Boomer_Ghost_G;
  INT m_iColor_Boomer_Ghost_B;
  INT m_iColor_Boomer_Spawned_R;
  INT m_iColor_Boomer_Spawned_G;
  INT m_iColor_Boomer_Spawned_B;
  INT m_iColor_Hunter_Ghost_R;
  INT m_iColor_Hunter_Ghost_G;
  INT m_iColor_Hunter_Ghost_B;
  INT m_iColor_Hunter_Spawned_R;
  INT m_iColor_Hunter_Spawned_G;
  INT m_iColor_Hunter_Spawned_B;
  INT m_iColor_Tank_Ghost_R;
  INT m_iColor_Tank_Ghost_G;
  INT m_iColor_Tank_Ghost_B;
  INT m_iColor_Tank_Spawned_R;
  INT m_iColor_Tank_Spawned_G;
  INT m_iColor_Tank_Spawned_B;

  INT m_iTextColor_R;
  INT m_iTextColor_G;
  INT m_iTextColor_B;

  FLOAT m_pfOldMatrix[16];
  BOOL m_bWasMatrixInitialized;

  BOOL m_bDrawESPBox;
  INT m_iBoxThickness;

  BOOL m_bDrawSkeleton;
  INT m_iSkeletonThickness;

  BOOL m_bDrawHealth;
  BOOL m_bDrawSnapLine;
};