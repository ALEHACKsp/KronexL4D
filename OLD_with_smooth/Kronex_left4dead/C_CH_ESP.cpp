#include <algorithm>    // std::sort
#include <sstream>

#include "C_CH_ESP.h"

C_CH_ESP::C_CH_ESP(C_CheatManager* cheatManager, string cheatName) : C_Cheat(cheatManager, cheatName)
{
  m_iColor_Smoker_Ghost_R = 255;
  m_iColor_Smoker_Ghost_G = 255;
  m_iColor_Smoker_Ghost_B = 0;
  m_iColor_Smoker_Spawned_R = 0;
  m_iColor_Smoker_Spawned_G = 255;
  m_iColor_Smoker_Spawned_B = 0;
  m_iColor_Boomer_Ghost_R = 255;
  m_iColor_Boomer_Ghost_G = 153;
  m_iColor_Boomer_Ghost_B = 153;
  m_iColor_Boomer_Spawned_R = 153;
  m_iColor_Boomer_Spawned_G = 0;
  m_iColor_Boomer_Spawned_B = 102;
  m_iColor_Hunter_Ghost_R = 0;
  m_iColor_Hunter_Ghost_G = 255;
  m_iColor_Hunter_Ghost_B = 255;
  m_iColor_Hunter_Spawned_R = 255;
  m_iColor_Hunter_Spawned_G = 0;
  m_iColor_Hunter_Spawned_B = 0;
  m_iColor_Tank_Ghost_R = 0;
  m_iColor_Tank_Ghost_G = 0;
  m_iColor_Tank_Ghost_B = 0;
  m_iColor_Tank_Spawned_R = 255;
  m_iColor_Tank_Spawned_G = 127;
  m_iColor_Tank_Spawned_B = 0;

  m_iTextColor_R = 0;
  m_iTextColor_G = 255;
  m_iTextColor_B = 255;

  m_iBoxThickness = 3;
  m_iSkeletonThickness = 5;

  m_bDrawESPBox = TRUE;
  m_bDrawSkeleton = FALSE;
  m_bDrawHealth = TRUE;
  m_bDrawSnapLine = FALSE;

  GetWindowRect(m_pCManager->m_GameWindow, &m_Rect);

  //m_iPerformSleepTime = 0;
  m_bWasMatrixInitialized = TRUE;
  m_iKeyCheatSwitchStatus = VK_NUMPAD5;
  m_bIsCheatEnabled = TRUE;
  m_bIsCheatInitialized = TRUE;
}

C_CH_ESP::~C_CH_ESP(VOID)
{
  
}

VOID C_CH_ESP::restoreChanges(VOID)
{

}

VOID C_CH_ESP::statusSwitched(VOID)
{

}


INT C_CH_ESP::findTargets(VOID)
{
  TargetList.clear();

  INT entitiesCount = m_pEManager->EntityList.size();

  for (INT i = 0; i < entitiesCount; i++)
  {
    C_Player* tempPlayer = m_pEManager->EntityList[i];

    if (tempPlayer->IsAlive()
        && (tempPlayer->Team() != m_pMyPlayer->Team() || (!m_pMyPlayer->IsAlive() && tempPlayer->Team() == m_pMyPlayer->Team()))
        && (tempPlayer->Team() == TeamInfect || tempPlayer->Team() == TeamSurv))
    {
      TargetList.push_back(tempPlayer);
    }
  }
  return TargetList.size();
}

BOOL C_CH_ESP::SortByHealthFunc(C_Player* player1, C_Player* player2)
{
  return (player1->Health() < player2->Health());
}

BOOL C_CH_ESP::SortByDistanceFunc(C_Player* player1, C_Player* player2)
{
  C_Player* myPlayer = C_CH_ESP::Instance->m_pMyPlayer;
  return (player1->DistanceTo(myPlayer) < player2->DistanceTo(myPlayer));
}

BOOL C_CH_ESP::sortTargets(TargetSortTypes sortType)
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
      case SortByDistance:
      {
        sort(TargetList.begin(), TargetList.end(), SortByDistanceFunc);
        return TRUE;
      }
      case SortByHealth:
      {
        sort(TargetList.begin(), TargetList.end(), SortByHealthFunc);
        return TRUE;
      }
      default:
      {
        return FALSE;
      }
    }
  }
}

VOID C_CH_ESP::perform(VOID)
{
  if (m_bIsCheatEnabled)
  {
    if (*m_pCManager->m_piIsPlayerOnServer == 1
        && *m_pCManager->m_piIsESCPressed == 0
        && *m_pCManager->m_piIsOverlayRendered == 0)
    {
      if (findTargets() > 0)
      {
        if (m_bDrawSnapLine) sortTargets(SortByDistance);

        INT targetsCount = TargetList.size();
        FLOAT EnemyXY[2];
        for (INT i = 0; i < targetsCount; i++)
        {
          if (WorldToScreen(TargetList[i]->BonePos(10), EnemyXY))
          {
            DrawESP((INT)(EnemyXY[0] - m_Rect.left), (INT)(EnemyXY[1] - m_Rect.top), TargetList[i]);
            if (m_bDrawSnapLine && i == 0)
            {
              DrawLine((m_Rect.right - m_Rect.left) / 2, m_Rect.bottom - m_Rect.top, (INT)(EnemyXY[0] - m_Rect.left), (INT)(EnemyXY[1] - m_Rect.top), m_iBoxThickness, SnapLineCOLOR);
            }
          }
        }
      }
    }
  }
}

VOID C_CH_ESP::DrawESP(INT x, INT y, C_Player* target)
{
  FLOAT chartype_width_factor = 1.0f;
  FLOAT chartype_height_factor = 1.0f;
  FLOAT distance = StaticFunctions::Get3dDistance(m_pMyPlayer->Position(), target->BonePos(10));

  switch (target->CharType())
  {
    case CharacterType_BOOMER: { chartype_width_factor = 18.0f; chartype_height_factor = 0.9f; break; }
    case CharacterType_HUNTER: { chartype_width_factor = 14.0f; chartype_height_factor = 0.7f; break; }
    case CharacterType_SMOKER: { chartype_width_factor = 14.0f; chartype_height_factor = 1.0f; break; }
    case CharacterType_TANK: { chartype_width_factor = 30.0f; chartype_height_factor = 1.0f; break; }
    default: { chartype_width_factor = 20.0f; chartype_height_factor = 0.8f; break; }
  }

  INT width = (INT)(m_pCManager->m_piScreenResolution[0] * chartype_width_factor / distance);
  INT height = (INT)(target->YDiff() * m_pCManager->m_piScreenResolution[1] * chartype_height_factor / distance);

  COLORREF espColor;

  switch (target->Team())
  {
    case TeamInfect:
    {
      switch (target->IsSpawned())
      {
        case 0:
        {
          switch (target->CharType())
          {
            case CharacterType_SMOKER:
            {
              espColor = RGB(m_iColor_Smoker_Ghost_R, m_iColor_Smoker_Ghost_G, m_iColor_Smoker_Ghost_B);
              break;
            }
            case CharacterType_BOOMER:
            {
              espColor = RGB(m_iColor_Boomer_Ghost_R, m_iColor_Boomer_Ghost_G, m_iColor_Boomer_Ghost_B);
              break;
            }
            case CharacterType_HUNTER:
            {
              espColor = RGB(m_iColor_Hunter_Ghost_R, m_iColor_Hunter_Ghost_G, m_iColor_Hunter_Ghost_B);
              break;
            }
            case CharacterType_TANK:
            {
              espColor = RGB(m_iColor_Tank_Ghost_R, m_iColor_Tank_Ghost_G, m_iColor_Tank_Ghost_B);
              break;
            }
            default:
            {
              espColor = COLOR_GRAY;
              break;
            }
          }
          break;
        }
        case 1:
        {
          switch (target->CharType())
          {
            case CharacterType_SMOKER:
            {
              espColor = RGB(m_iColor_Smoker_Spawned_R, m_iColor_Smoker_Spawned_G, m_iColor_Smoker_Spawned_B);
              break;
            }
            case CharacterType_BOOMER:
            {
              espColor = RGB(m_iColor_Boomer_Spawned_R, m_iColor_Boomer_Spawned_G, m_iColor_Boomer_Spawned_B);
              break;
            }
            case CharacterType_HUNTER:
            {
              espColor = RGB(m_iColor_Hunter_Spawned_R, m_iColor_Hunter_Spawned_G, m_iColor_Hunter_Spawned_B);
              break;
            }
            case CharacterType_TANK:
            {
              espColor = RGB(m_iColor_Tank_Spawned_R, m_iColor_Tank_Spawned_G, m_iColor_Tank_Spawned_B);
              break;
            }
            default:
            {
              espColor = COLOR_GRAY;
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case TeamSurv:
    {
      INT health = target->Health();
      if (health > 50)
      {
        espColor = COLOR_GREEN;
      }
      else if (health > 15 && health <= 50)
      {
        espColor = COLOR_ORANGE;
      }
      else if (health > 0 && health <= 15)
      {
        espColor = COLOR_RED;
      }
      break;
    }
  }

  if(m_bDrawESPBox) DrawBorderBox(x - (width / 2), y - (height / 2), width, height, m_iBoxThickness, espColor);

  if (m_bDrawSkeleton)
  {
    FLOAT Point1[2];
    FLOAT Point2[2];

    for (int i = 0; i < 4; i++)
    {
      if (WorldToScreen(target->BonePos(i), Point1))
      {
        if (WorldToScreen(target->BonePos(i + 1), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
    }
    if (WorldToScreen(target->BonePos(0), Point1))
    {
      if (WorldToScreen(target->BonePos(5), Point2))
      {
        DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
      }
    }
    for (int i = 5; i < 8; i++)
    {
      if (WorldToScreen(target->BonePos(i), Point1))
      {
        if (WorldToScreen(target->BonePos(i + 1), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
    }
    if (WorldToScreen(target->BonePos(0), Point1))
    {
      if (WorldToScreen(target->BonePos(9), Point2))
      {
        DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
      }
    }
    for (int i = 9; i < 13; i++)
    {
      if (WorldToScreen(target->BonePos(i), Point1))
      {
        if (WorldToScreen(target->BonePos(i + 1), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
    }
    //if (WorldToScreen(target->BonePos(14), Point1))
    //{
    //  if (WorldToScreen(target->BonePos(14), Point2))
    //  {
    //    DrawFilledRect((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, 10, 10, RGB(255, 0, 0)); // !X!
    //  }
    //}
    if (WorldToScreen(target->BonePos(13), Point1))
    {
      if (WorldToScreen(target->BonePos(16), Point2))
      {
        DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
      }
    }
    for (int i = 16; i < 18; i++)
    {
      if (WorldToScreen(target->BonePos(i), Point1))
      {
        if (WorldToScreen(target->BonePos(i + 1), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
    }
    if (target->CharType() == CharacterType_BOOMER || target->CharType() == CharacterType_SMOKER)
    {
      if (WorldToScreen(target->BonePos(13), Point1))
      {
        if (WorldToScreen(target->BonePos(20), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
      for (int i = 20; i < 22; i++)
      {
        if (WorldToScreen(target->BonePos(i), Point1))
        {
          if (WorldToScreen(target->BonePos(i + 1), Point2))
          {
            DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
          }
        }
      }
    }
    else
    {
      if (WorldToScreen(target->BonePos(13), Point1))
      {
        if (WorldToScreen(target->BonePos(35), Point2))
        {
          DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
        }
      }
      for (int i = 35; i < 37; i++)
      {
        if (WorldToScreen(target->BonePos(i), Point1))
        {
          if (WorldToScreen(target->BonePos(i + 1), Point2))
          {
            DrawLine((INT)Point1[0] - m_Rect.left, (INT)Point1[1] - m_Rect.top, (INT)Point2[0] - m_Rect.left, (INT)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor); // !X!
          }
        }
      }
    }
  }

  if (m_bDrawHealth)
  {
    stringstream Health;
    stringstream CharType;

    Health << target->Health();

    PCHAR HealthText = new char[Health.str().size() + 1];

    strcpy_s(HealthText, Health.str().size() + 1, Health.str().c_str());

    DrawString(x, y - (height / 2) - 20, RGB(m_iTextColor_R, m_iTextColor_G, m_iTextColor_B), HealthText);

    delete[] HealthText;
  }
}

VOID C_CH_ESP::DrawLine(INT StartX, INT StartY, INT EndX, INT EndY, INT thickness, COLORREF CurrentColor)
{
  INT a;
  INT b = 0;
  HPEN hOPen;
  HPEN hNPen = CreatePen(PS_SOLID, thickness, CurrentColor);
  hOPen = (HPEN)SelectObject(m_pCManager->m_HDC_Desktop, hNPen);
  MoveToEx(m_pCManager->m_HDC_Desktop, StartX, StartY, NULL);
  a = LineTo(m_pCManager->m_HDC_Desktop, EndX, EndY);
  DeleteObject(SelectObject(m_pCManager->m_HDC_Desktop, hOPen));
}

VOID C_CH_ESP::DrawBorderBox(INT x, INT y, INT w, INT h, INT thickness, COLORREF CurrentColor)
{
  DrawFilledRect(x, y, w, thickness, CurrentColor);
  DrawFilledRect(x, y, thickness, h, CurrentColor);
  DrawFilledRect(x + w, y, thickness, h, CurrentColor);
  DrawFilledRect(x, y + h, w + thickness, thickness, CurrentColor);
}

VOID C_CH_ESP::DrawFilledRect(INT x, INT y, INT w, INT h, COLORREF CurrentColor)
{
  RECT rect = { x, y, x + w, y + h };
  HBRUSH hbrush = CreateSolidBrush(CurrentColor);
  FillRect(m_pCManager->m_HDC_Desktop, &rect, hbrush);
  DeleteObject(hbrush);
}

VOID C_CH_ESP::DrawString(INT x, INT y, COLORREF color, CONST PCHAR text)
{
  SetTextAlign(m_pCManager->m_HDC_Desktop, TA_CENTER | TA_NOUPDATECP);

  SetBkColor(m_pCManager->m_HDC_Desktop, COLOR_BLACK);
  SetBkMode(m_pCManager->m_HDC_Desktop, OPAQUE);

  SetTextColor(m_pCManager->m_HDC_Desktop, color);

  SelectObject(m_pCManager->m_HDC_Desktop, m_Font);

  TextOutA(m_pCManager->m_HDC_Desktop, x, y, text, strlen(text));

  DeleteObject(m_Font);
}

BOOL C_CH_ESP::WorldToScreen(PFLOAT from, PFLOAT to)
{
  FLOAT world = 0.0f;

  PFLOAT matrix;

  if (*(PINT)(m_pCManager->m_dwEngineDll + 0x520B60) == 1) // flicker
  {
    matrix = m_pCManager->m_pfWorldToScreenMatrix;
    for(INT i = 0; i < 16; i++) m_pfOldMatrix[i] = matrix[i];
    m_bWasMatrixInitialized = TRUE;
  }
  else
  {
    if(m_bWasMatrixInitialized == TRUE) matrix = m_pfOldMatrix;
    else
    {
      matrix = m_pCManager->m_pfWorldToScreenMatrix;
      for (INT i = 0; i < 16; i++) m_pfOldMatrix[i] = matrix[i];
      m_bWasMatrixInitialized = TRUE;
    }
  }

  to[0] = matrix[0] * from[0] +
          matrix[1] * from[1] +
          matrix[2] * from[2] +
          matrix[3];

  to[1] = matrix[4] * from[0] +
          matrix[5] * from[1] +
          matrix[6] * from[2] +
          matrix[7];

  world = matrix[12] * from[0] +
          matrix[13] * from[1] +
          matrix[14] * from[2] +
          matrix[15];

  if (world > 1.0f) // 0.01f
  {
    FLOAT invw = 1.0f / world;
    to[0] *= invw;
    to[1] *= invw;

    INT width = (INT)(m_Rect.right - m_Rect.left);
    INT height = (INT)(m_Rect.bottom - m_Rect.top);

    FLOAT x = width / 2.0f;
    FLOAT y = height / 2.0f;

    x += 0.5f * to[0] * width + 0.5f;
    y -= 0.5f * to[1] * height + 0.5f;

    to[0] = x + m_Rect.left;
    to[1] = y + m_Rect.top;

    return TRUE;
  }
  else
  {
    to[0] = -1.0f;
    to[1] = -1.0f;
  }

  return FALSE;
}