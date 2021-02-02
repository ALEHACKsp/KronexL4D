#include "KronexMain.h"

C_CH_ESP::C_CH_ESP(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_esp_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_ghost_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_ghost_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_ghost_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_spawned_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_spawned_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_smoker_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_ghost_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_ghost_g"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_ghost_b"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_spawned_r"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_spawned_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_boomer_spawned_b"), XS("102"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_ghost_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_ghost_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_ghost_b"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_spawned_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_spawned_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_hunter_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_ghost_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_ghost_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_ghost_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_spawned_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_spawned_g"), XS("127"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_tank_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_textcolor_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_textcolor_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_textcolor_b"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_box"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_thickness_box"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_skeleton"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_thickness_skeleton"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_snapline"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_thickness_snapline"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_health"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_health_visual"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_nickname"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_draw_tank_frustration"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_esp_drawstyle"), to_string(DRAW_BY_BONEMATRIX).c_str(), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  m_iPerformSleepTime = 100;

  m_bIsCheatInitialized = true;
}

C_CH_ESP::~C_CH_ESP()
{
  C_CVarMgr::UnRegConVar(XS("krx_esp_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_smoker_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_boomer_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_hunter_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_tank_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_textcolor_r"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_textcolor_g"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_textcolor_b"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_box"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_thickness_box"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_skeleton"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_thickness_skeleton"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_snapline"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_thickness_snapline"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_health"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_health_visual"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_nickname"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_draw_tank_frustration"));
  C_CVarMgr::UnRegConVar(XS("krx_esp_drawstyle"));
  
}

void C_CH_ESP::restoreChanges()
{

}

int C_CH_ESP::findTargets()
{
  TargetList.clear();

  int entitiesCount = pEMgr->EntityList.size();

  for (int i = 0; i < entitiesCount; i++)
  {
    C_Player* tempPlayer = pEMgr->EntityList[i];

    if (tempPlayer->IsAlive()
        && (tempPlayer->Team() != m_pPlayer->Team() || (!m_pPlayer->IsAlive() && tempPlayer->Team() == m_pPlayer->Team()))
        && (tempPlayer->Team() == TEAM_INFECT || tempPlayer->Team() == TEAM_SURV))
    {
      if (PlayerBoneToScreen(tempPlayer, 10))
      {
        TargetList.push_back(tempPlayer);
      }
    }
  }
  return TargetList.size();
}

void C_CH_ESP::update()
{
  g_pEngineClient->GetScreenSize(m_iScreen_X, m_iScreen_Y);

  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_esp_enabled"))->GetInt() == 1 ? true : false;
  m_iColor_Smoker_Ghost_R = C_CVarMgr::FindVar(XS("krx_esp_smoker_ghost_r"))->GetInt();
  m_iColor_Smoker_Ghost_G = C_CVarMgr::FindVar(XS("krx_esp_smoker_ghost_g"))->GetInt();
  m_iColor_Smoker_Ghost_B = C_CVarMgr::FindVar(XS("krx_esp_smoker_ghost_b"))->GetInt();
  m_iColor_Smoker_Spawned_R = C_CVarMgr::FindVar(XS("krx_esp_smoker_spawned_r"))->GetInt();
  m_iColor_Smoker_Spawned_G = C_CVarMgr::FindVar(XS("krx_esp_smoker_spawned_g"))->GetInt();
  m_iColor_Smoker_Spawned_B = C_CVarMgr::FindVar(XS("krx_esp_smoker_spawned_b"))->GetInt();
  m_iColor_Boomer_Ghost_R = C_CVarMgr::FindVar(XS("krx_esp_boomer_ghost_r"))->GetInt();
  m_iColor_Boomer_Ghost_G = C_CVarMgr::FindVar(XS("krx_esp_boomer_ghost_g"))->GetInt();
  m_iColor_Boomer_Ghost_B = C_CVarMgr::FindVar(XS("krx_esp_boomer_ghost_b"))->GetInt();
  m_iColor_Boomer_Spawned_R = C_CVarMgr::FindVar(XS("krx_esp_boomer_spawned_r"))->GetInt();
  m_iColor_Boomer_Spawned_G = C_CVarMgr::FindVar(XS("krx_esp_boomer_spawned_g"))->GetInt();
  m_iColor_Boomer_Spawned_B = C_CVarMgr::FindVar(XS("krx_esp_boomer_spawned_b"))->GetInt();
  m_iColor_Hunter_Ghost_R = C_CVarMgr::FindVar(XS("krx_esp_hunter_ghost_r"))->GetInt();
  m_iColor_Hunter_Ghost_G = C_CVarMgr::FindVar(XS("krx_esp_hunter_ghost_g"))->GetInt();
  m_iColor_Hunter_Ghost_B = C_CVarMgr::FindVar(XS("krx_esp_hunter_ghost_b"))->GetInt();
  m_iColor_Hunter_Spawned_R = C_CVarMgr::FindVar(XS("krx_esp_hunter_spawned_r"))->GetInt();
  m_iColor_Hunter_Spawned_G = C_CVarMgr::FindVar(XS("krx_esp_hunter_spawned_g"))->GetInt();
  m_iColor_Hunter_Spawned_B = C_CVarMgr::FindVar(XS("krx_esp_hunter_spawned_b"))->GetInt();
  m_iColor_Tank_Ghost_R = C_CVarMgr::FindVar(XS("krx_esp_tank_ghost_r"))->GetInt();
  m_iColor_Tank_Ghost_G = C_CVarMgr::FindVar(XS("krx_esp_tank_ghost_g"))->GetInt();
  m_iColor_Tank_Ghost_B = C_CVarMgr::FindVar(XS("krx_esp_tank_ghost_b"))->GetInt();
  m_iColor_Tank_Spawned_R = C_CVarMgr::FindVar(XS("krx_esp_tank_spawned_r"))->GetInt();
  m_iColor_Tank_Spawned_G = C_CVarMgr::FindVar(XS("krx_esp_tank_spawned_g"))->GetInt();
  m_iColor_Tank_Spawned_B = C_CVarMgr::FindVar(XS("krx_esp_tank_spawned_b"))->GetInt();
  m_iTextColor_R = C_CVarMgr::FindVar(XS("krx_esp_textcolor_r"))->GetInt();
  m_iTextColor_G = C_CVarMgr::FindVar(XS("krx_esp_textcolor_g"))->GetInt();
  m_iTextColor_B = C_CVarMgr::FindVar(XS("krx_esp_textcolor_b"))->GetInt();
  m_bDrawESPBox = C_CVarMgr::FindVar(XS("krx_esp_draw_box"))->GetInt() == 1 ? true : false;
  m_iBoxThickness = C_CVarMgr::FindVar(XS("krx_esp_thickness_box"))->GetInt();
  m_bDrawSkeleton = C_CVarMgr::FindVar(XS("krx_esp_draw_skeleton"))->GetInt() == 1 ? true : false;
  m_iSkeletonThickness = C_CVarMgr::FindVar(XS("krx_esp_thickness_skeleton"))->GetInt();
  m_bDrawSnapLine = C_CVarMgr::FindVar(XS("krx_esp_draw_snapline"))->GetInt() == 1 ? true : false;
  m_iSnapLineThickness = C_CVarMgr::FindVar(XS("krx_esp_thickness_snapline"))->GetInt();
  m_bDrawHealth = C_CVarMgr::FindVar(XS("krx_esp_draw_health"))->GetInt() == 1 ? true : false;
  m_bDrawHealthVisual = C_CVarMgr::FindVar(XS("krx_esp_draw_health_visual"))->GetInt() == 1 ? true : false;
  m_bDrawNickName = C_CVarMgr::FindVar(XS("krx_esp_draw_nickname"))->GetInt() == 1 ? true : false;
  m_bDrawTankFrustration = C_CVarMgr::FindVar(XS("krx_esp_draw_tank_frustration"))->GetInt() == 1 ? true : false;
  m_iDrawStyle = C_CVarMgr::FindVar(XS("krx_esp_drawstyle"))->GetInt();
  
}

void C_CH_ESP::perform()
{
  if (IS_EXEC_ALLOWED)
  {

  }
}

Color C_CH_ESP::GetColor(C_Player* target)
{
  Color espColor;
  switch (target->Team())
  {
    case TEAM_INFECT:
    {
      switch (target->IsSpawned())
      {
        case 0:
        {
          switch (target->CharType())
          {
            case CHARACTER_TYPE_SMOKER:
            {
              espColor.SetColor(
                m_iColor_Smoker_Ghost_R,
                m_iColor_Smoker_Ghost_G,
                m_iColor_Smoker_Ghost_B, 255);
              break;
            }
            case CHARACTER_TYPE_BOOMER:
            {
              espColor.SetColor(
                m_iColor_Boomer_Ghost_R,
                m_iColor_Boomer_Ghost_G,
                m_iColor_Boomer_Ghost_B, 255);
              break;
            }
            case CHARACTER_TYPE_HUNTER:
            {
              espColor.SetColor(
                m_iColor_Hunter_Ghost_R,
                m_iColor_Hunter_Ghost_G,
                m_iColor_Hunter_Ghost_B, 255);
              break;
            }
            case CHARACTER_TYPE_TANK:
            {
              espColor.SetColor(
                m_iColor_Tank_Ghost_R,
                m_iColor_Tank_Ghost_G,
                m_iColor_Tank_Ghost_B, 255);
              break;
            }
            default:
            {
              espColor.SetColor(204, 204, 204, 255);
              break;
            }
          }
          break;
        }
        case 1:
        {
          switch (target->CharType())
          {
            case CHARACTER_TYPE_SMOKER:
            {
              espColor.SetColor(
                m_iColor_Smoker_Spawned_R,
                m_iColor_Smoker_Spawned_G,
                m_iColor_Smoker_Spawned_B, 255);
              break;
            }
            case CHARACTER_TYPE_BOOMER:
            {
              espColor.SetColor(
                m_iColor_Boomer_Spawned_R,
                m_iColor_Boomer_Spawned_G,
                m_iColor_Boomer_Spawned_B, 255);
              break;
            }
            case CHARACTER_TYPE_HUNTER:
            {
              espColor.SetColor(
                m_iColor_Hunter_Spawned_R,
                m_iColor_Hunter_Spawned_G,
                m_iColor_Hunter_Spawned_B, 255);
              break;
            }
            case CHARACTER_TYPE_TANK:
            {
              espColor.SetColor(
                m_iColor_Tank_Spawned_R,
                m_iColor_Tank_Spawned_G,
                m_iColor_Tank_Spawned_B, 255);
              break;
            }
            default:
            {
              espColor.SetColor(204, 204, 204, 255);
              break;
            }
          }
          break;
        }
      }
      break;
    }
    case TEAM_SURV:
    {
      int health = target->Health();
      if (health > 50)
      {
        espColor.SetColor(0, 255, 0, 255);
      }
      else if (health > 15 && health <= 50)
      {
        espColor.SetColor(255, 127, 0, 255);
      }
      else if (health > 0 && health <= 15)
      {
        espColor.SetColor(255, 0, 0, 255);
      }
      break;
    }
  }
  return espColor;
}

bool C_CH_ESP::PlayerBoneToScreen(C_Player* pPlayer, int boneID)
{
  float from[3];

  if (m_iDrawStyle == DRAW_BY_HITBOX)
  {
    float* tempPos = pPlayer->Position();
    from[0] = tempPos[0];
    from[1] = tempPos[1];
    from[2] = tempPos[2] + 32.0f;
  }
  else
  {
    float* tempPos = pPlayer->BonePos(boneID);
    from[0] = tempPos[0];
    from[1] = tempPos[1];
    from[2] = tempPos[2];
  }

  float world = 0.0f;

  float* matrix = (float*)g_pEngineClient->WorldToScreenMatrix();

  pPlayer->vBonePos[boneID].x = matrix[0] * from[0] + matrix[1] * from[1] + matrix[2] * from[2] + matrix[3];
  pPlayer->vBonePos[boneID].y = matrix[4] * from[0] + matrix[5] * from[1] + matrix[6] * from[2] + matrix[7];

  world = matrix[12] * from[0] + matrix[13] * from[1] + matrix[14] * from[2] + matrix[15];

  if (world > 0.01f) // 0.01f
  {
    pPlayer->vBonePos[boneID].x /= world;
    pPlayer->vBonePos[boneID].y /= world;

    float x = m_iScreen_X / 2.0f;
    float y = m_iScreen_Y / 2.0f;

    x += 0.5f * pPlayer->vBonePos[boneID].x * m_iScreen_X + 0.5f;
    y -= 0.5f * pPlayer->vBonePos[boneID].y * m_iScreen_Y + 0.5f;

    pPlayer->vBonePos[boneID].x = x;
    pPlayer->vBonePos[boneID].y = y;

    return true;
  }

  return false;
}
