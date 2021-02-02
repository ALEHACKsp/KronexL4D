#include "KronexMain.h"

C_CH_Radar::C_CH_Radar(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_radar_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_pos_x"), XS("70"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_pos_y"), XS("70"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_drawradius"), XS("50"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_range"), XS("500"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_segments"), XS("10"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_point_size"), XS("2"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_point_segments"), XS("8"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_ghost_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_ghost_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_ghost_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_spawned_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_spawned_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_smoker_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_ghost_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_ghost_g"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_ghost_b"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_spawned_r"), XS("153"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_spawned_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_boomer_spawned_b"), XS("102"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_ghost_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_ghost_g"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_ghost_b"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_spawned_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_spawned_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_hunter_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_ghost_r"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_ghost_g"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_ghost_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_spawned_r"), XS("255"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_spawned_g"), XS("127"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_tank_spawned_b"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_draw_fovlines"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_radar_draw_fovbg"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);


  m_iPerformSleepTime = 100;
  m_bIsCheatInitialized = true;
}

C_CH_Radar::~C_CH_Radar()
{
  C_CVarMgr::UnRegConVar(XS("krx_radar_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_pos_x"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_pos_y"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_drawradius"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_range"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_segments"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_point_size"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_point_segments"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_smoker_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_boomer_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_hunter_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_ghost_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_ghost_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_ghost_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_spawned_r"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_spawned_g"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_tank_spawned_b"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_draw_fovlines"));
  C_CVarMgr::UnRegConVar(XS("krx_radar_draw_fovbg"));
}

void C_CH_Radar::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_radar_enabled"))->GetInt() == 1 ? true : false;

  m_iPos_X = C_CVarMgr::FindVar(XS("krx_radar_pos_x"))->GetInt();
  m_iPos_Y = C_CVarMgr::FindVar(XS("krx_radar_pos_y"))->GetInt();
  m_iDrawRadius = C_CVarMgr::FindVar(XS("krx_radar_drawradius"))->GetInt();
  m_flRange = C_CVarMgr::FindVar(XS("krx_radar_range"))->GetInt();
  m_iSegments = C_CVarMgr::FindVar(XS("krx_radar_segments"))->GetInt();
  m_iPointSize = C_CVarMgr::FindVar(XS("krx_radar_point_size"))->GetInt();
  m_iPointSegments = C_CVarMgr::FindVar(XS("krx_radar_point_segments"))->GetInt();

  m_iColor_Smoker_Ghost_R = C_CVarMgr::FindVar(XS("krx_radar_smoker_ghost_r"))->GetInt();
  m_iColor_Smoker_Ghost_G = C_CVarMgr::FindVar(XS("krx_radar_smoker_ghost_g"))->GetInt();
  m_iColor_Smoker_Ghost_B = C_CVarMgr::FindVar(XS("krx_radar_smoker_ghost_b"))->GetInt();
  m_iColor_Smoker_Spawned_R = C_CVarMgr::FindVar(XS("krx_radar_smoker_spawned_r"))->GetInt();
  m_iColor_Smoker_Spawned_G = C_CVarMgr::FindVar(XS("krx_radar_smoker_spawned_g"))->GetInt();
  m_iColor_Smoker_Spawned_B = C_CVarMgr::FindVar(XS("krx_radar_smoker_spawned_b"))->GetInt();
  m_iColor_Boomer_Ghost_R = C_CVarMgr::FindVar(XS("krx_radar_boomer_ghost_r"))->GetInt();
  m_iColor_Boomer_Ghost_G = C_CVarMgr::FindVar(XS("krx_radar_boomer_ghost_g"))->GetInt();
  m_iColor_Boomer_Ghost_B = C_CVarMgr::FindVar(XS("krx_radar_boomer_ghost_b"))->GetInt();
  m_iColor_Boomer_Spawned_R = C_CVarMgr::FindVar(XS("krx_radar_boomer_spawned_r"))->GetInt();
  m_iColor_Boomer_Spawned_G = C_CVarMgr::FindVar(XS("krx_radar_boomer_spawned_g"))->GetInt();
  m_iColor_Boomer_Spawned_B = C_CVarMgr::FindVar(XS("krx_radar_boomer_spawned_b"))->GetInt();
  m_iColor_Hunter_Ghost_R = C_CVarMgr::FindVar(XS("krx_radar_hunter_ghost_r"))->GetInt();
  m_iColor_Hunter_Ghost_G = C_CVarMgr::FindVar(XS("krx_radar_hunter_ghost_g"))->GetInt();
  m_iColor_Hunter_Ghost_B = C_CVarMgr::FindVar(XS("krx_radar_hunter_ghost_b"))->GetInt();
  m_iColor_Hunter_Spawned_R = C_CVarMgr::FindVar(XS("krx_radar_hunter_spawned_r"))->GetInt();
  m_iColor_Hunter_Spawned_G = C_CVarMgr::FindVar(XS("krx_radar_hunter_spawned_g"))->GetInt();
  m_iColor_Hunter_Spawned_B = C_CVarMgr::FindVar(XS("krx_radar_hunter_spawned_b"))->GetInt();
  m_iColor_Tank_Ghost_R = C_CVarMgr::FindVar(XS("krx_radar_tank_ghost_r"))->GetInt();
  m_iColor_Tank_Ghost_G = C_CVarMgr::FindVar(XS("krx_radar_tank_ghost_g"))->GetInt();
  m_iColor_Tank_Ghost_B = C_CVarMgr::FindVar(XS("krx_radar_tank_ghost_b"))->GetInt();
  m_iColor_Tank_Spawned_R = C_CVarMgr::FindVar(XS("krx_radar_tank_spawned_r"))->GetInt();
  m_iColor_Tank_Spawned_G = C_CVarMgr::FindVar(XS("krx_radar_tank_spawned_g"))->GetInt();
  m_iColor_Tank_Spawned_B = C_CVarMgr::FindVar(XS("krx_radar_tank_spawned_b"))->GetInt();

  m_bDrawFovLines = C_CVarMgr::FindVar(XS("krx_radar_draw_fovlines"))->GetInt() == 1 ? true : false;
  m_bDrawFovBackGround = C_CVarMgr::FindVar(XS("krx_radar_draw_fovbg"))->GetInt() == 1 ? true : false;
}


int C_CH_Radar::findTargets()
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
       TargetList.push_back(tempPlayer);
    }
  }
  return TargetList.size();
}

void C_CH_Radar::perform()
{
  if (IS_EXEC_ALLOWED)
  {

  }
}

void C_CH_Radar::restoreChanges()
{

}

Color C_CH_Radar::GetColor(C_Player* target)
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