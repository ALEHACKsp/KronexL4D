#include "KronexMain.h"

C_CH_Aimbot::C_CH_Aimbot(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_aimbot_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_key_use"), XS("160"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_fov"), XS("15.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_silent"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_silent_delta1"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_silent_delta2"), XS("5000"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_autoshoot"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_smooth"), XS("20.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_pistol"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_smg"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_pumpshotgun"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_autoshotgun"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_rifle"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_range_huntingrifle"), XS("10000.0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_bone"), XS("11"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_action_after_shoot"), XS("\"slot2; wait 10; slot1;\""), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_action_after_shoot_timer"), XS("65"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);
  C_CVarMgr::RegConVar(XS("krx_aimbot_targetdetect_type"), XS("0"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN); // 0-angle, 1-health, 2-distance

  m_bShooted = false;

  m_iTimeLastShoot = 0;
  m_iPerformSleepTime = 1;
  m_bIsCheatInitialized = true;
  //m_bIsCheatInitialized = false;
}

C_CH_Aimbot::~C_CH_Aimbot()
{
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_enabled"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_key_use"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_fov"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_silent"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_silent_delta1"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_silent_delta2"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_smooth"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_autoshoot"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_pistol"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_smg"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_pumpshotgun"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_autoshotgun"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_rifle"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_range_huntingrifle"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_bone"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_action_after_shoot"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_action_after_shoot_timer"));
  C_CVarMgr::UnRegConVar(XS("krx_aimbot_targetdetect_type"));
}

int C_CH_Aimbot::GetBestBone(C_Player* target)
{
  if (m_iBoneNumber == 10 || m_iBoneNumber == 11 || m_iBoneNumber == 10)
  {
    if (m_iMyWeapon == WEAPON_ID_PISTOL
      || m_iMyWeapon == WEAPON_ID_SMG
      || m_iMyWeapon == WEAPON_ID_RIFLE
      || m_iMyWeapon == WEAPON_ID_HUNTINGRIFLE)
    {
      return 14;
    }
    return 11;
  }
  else return m_iBoneNumber;
}

int C_CH_Aimbot::findTargets()
{
	TargetList.clear();
  if (!(m_pPlayer->Team() == TEAM_SURV) || !m_pPlayer->IsAlive() || !m_pPlayer->IsSpawned()) return NULL;

	int entitiesCount = pEMgr->EntityList.size();

	for (int i = 0; i < entitiesCount; i++)
	{
    C_Player *tempPlayer = pEMgr->EntityList[i];

    if (tempPlayer->Team() == TEAM_INFECT
			  && tempPlayer->IsAlive()
			  && tempPlayer->IsSpawned())
		{
			tempPlayer->CalculateAngleTo(m_pPlayer, m_iBoneNumber);
      TargetList.push_back(tempPlayer);
		}
	}
	return TargetList.size();
}

bool C_CH_Aimbot::SortByHealthFunc(C_Player* player1, C_Player* player2)
{
	return (player1->Health() < player2->Health());
}

bool C_CH_Aimbot::SortByDistanceFunc(C_Player* player1, C_Player* player2)
{
  C_Player* myPlayer = ((C_CH_Aimbot*)C_CheatMgr::GetCheat(XS("C_CH_Aimbot")))->m_pPlayer;
	return (player1->DistanceTo(myPlayer) < player2->DistanceTo(myPlayer));
}

bool C_CH_Aimbot::SortByAngleFunc(C_Player* player1, C_Player* player2)
{
  float ang1[] = { pCmd->viewangles[0], pCmd->viewangles[1], pCmd->viewangles[2] };
  float ang2[] = { pCmd->viewangles[0], pCmd->viewangles[1], pCmd->viewangles[2] };

	float AngleDistance1 = Utils::GetAngleDistance(ang1, player1->GetAngle());
	float AngleDistance2 = Utils::GetAngleDistance(ang2, player2->GetAngle());

	return (AngleDistance1 < AngleDistance2);
}

bool C_CH_Aimbot::sortTargets()
{
  int TargetsCount = TargetList.size();

  if (TargetsCount < 1)
  {
    return false;
  }
  else if (TargetsCount == 1)
  {
    return true;
  }
  else
  {
    switch (m_iSortType)
    {
      case SORT_BY_ANGLE:
      {
        sort(TargetList.begin(), TargetList.end(), SortByAngleFunc);
        return true;
      }
      case SORT_BY_HEALTH:
      {
        sort(TargetList.begin(), TargetList.end(), SortByHealthFunc);
        return true;
      }
      case SORT_BY_DISTANCE:
      {
        sort(TargetList.begin(), TargetList.end(), SortByDistanceFunc);
        return true;
      }
      default:
      {
        return false;
      }
    }
  }
}

void C_CH_Aimbot::update()
{
  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_aimbot_enabled"))->GetInt() == 1 ? true : false;
  m_iKeyCheatUse = C_CVarMgr::FindVar(XS("krx_aimbot_key_use"))->GetInt();
  m_flFOV = C_CVarMgr::FindVar(XS("krx_aimbot_fov"))->GetFloat();
  m_bSilent = C_CVarMgr::FindVar(XS("krx_aimbot_silent"))->GetInt() == 1 ? true : false;
  m_bAutoShoot = C_CVarMgr::FindVar(XS("krx_aimbot_autoshoot"))->GetInt() == 1 ? true : false;
  m_flShotgunsSmooth = C_CVarMgr::FindVar(XS("krx_aimbot_smooth"))->GetFloat();
  m_iSilentDelta1 = C_CVarMgr::FindVar(XS("krx_aimbot_silent_delta1"))->GetInt();
  m_iSilentDelta2 = C_CVarMgr::FindVar(XS("krx_aimbot_silent_delta2"))->GetInt();
  m_iMyWeapon = m_pPlayer->CurWeapID();

  switch (m_iMyWeapon)
  {
    case WEAPON_ID_PISTOL:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_pistol"))->GetFloat();
      break;
    case WEAPON_ID_SMG:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_smg"))->GetFloat();
      break;
    case WEAPON_ID_PUMPSHOTGUN:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_pumpshotgun"))->GetFloat();
      break;
    case WEAPON_ID_AUTOSHOTGUN:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_autoshotgun"))->GetFloat();
      break;
    case WEAPON_ID_RIFLE:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_rifle"))->GetFloat();
      break;
    case WEAPON_ID_HUNTINGRIFLE:
      m_flRange = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_range_huntingrifle"))->GetFloat();
      break;
    default:
      m_flRange = 10000.0f;
      break;
  }
  m_iBoneNumber = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_bone"))->GetInt();
  m_sActionAfterShoot = C_CVarMgr::FindVar(XS("krx_aimbot_action_after_shoot"))->GetString();
  m_iActionAfterShootTimer = C_CVarMgr::FindVar(XS("krx_aimbot_action_after_shoot_timer"))->GetInt();
  m_iSortType = C_CVarMgr::FindVar(XS("krx_aimbot_targetdetect_type"))->GetInt();
}

void C_CH_Aimbot::perform()
{
  if (IS_EXEC_ALLOWED)
  {
    if (GetAsyncKeyState(m_iKeyCheatUse))
    {
      if (m_pPlayer->Team() == TEAM_SURV)
      {
        if (findTargets() > 0)
        {
          if (sortTargets())
          {
            float distanceToMyPlayer = TargetList[0]->DistanceTo(m_pPlayer);

            if (distanceToMyPlayer <= m_flRange)
            {
              float ang1[] = { pCmd->viewangles[0], pCmd->viewangles[1], pCmd->viewangles[2] };
              float angleToTarget = Utils::GetAngleDistance(ang1, TargetList[0]->GetAngle());

              if (angleToTarget <= m_flFOV)
              {
                if (IsAbleToShoot())
                {
                  if (m_iMyWeapon == WEAPON_ID_PISTOL
                      || m_iMyWeapon == WEAPON_ID_SMG
                      || m_iMyWeapon == WEAPON_ID_RIFLE
                      || m_iMyWeapon == WEAPON_ID_HUNTINGRIFLE
                      || m_iMyWeapon == WEAPON_ID_PUMPSHOTGUN
                      || m_iMyWeapon == WEAPON_ID_AUTOSHOTGUN)
                  {
                    TargetList[0]->CalculateAngleTo(m_pPlayer, GetBestBone(TargetList[0]));

                    if (m_bSilent)
                    {
                      //if (clock() - m_iTimeLastShoot > m_iSilentDelta1/*3*//*(int)(g_pGlobalsClient->interval_per_tick * 1000)*/)
                      {
                        pCMgr->SendPacketStatus(false);

                        pCmd->viewangles[0] = TargetList[0]->GetAngle()[0];
                        pCmd->viewangles[1] = TargetList[0]->GetAngle()[1];
                        pCmd->buttons &= ~IN_RELOAD;
                        pCmd->buttons &= ~IN_ATTACK2;
                        pCmd->buttons |= IN_ATTACK;

                        if (m_iMyWeapon == WEAPON_ID_PUMPSHOTGUN
                            || m_iMyWeapon == WEAPON_ID_AUTOSHOTGUN)
                        {
                          pCmd->hasbeenpredicted = false;
                        }

                        m_bShooted = true;
                        pCMgr->SendPacketStatus(false);

                        this_thread::sleep_for(chrono::milliseconds(m_iSilentDelta1));
                        
                        //m_iTimeLastShoot = clock();
                        pCMgr->SendPacketStatus(true);

                        this_thread::sleep_for(chrono::milliseconds(m_iSilentDelta2));
                      }
                    }
                    else
                    {
                      if (!m_bShooted)
                      {
                        if (m_bAutoShoot)
                        {
                          for (float i = 0.0f; i < m_flShotgunsSmooth && TargetList[0]->IsAlive(); i++)
                          {
                            TargetList[0]->CalculateAngleTo(m_pPlayer, GetBestBone(TargetList[0]));

                            Vector vOldViewAngles;
                            g_pEngineClient->GetViewAngles(vOldViewAngles);

                            Vector vTargetAngles;
                            vTargetAngles[0] = TargetList[0]->GetAngle()[0];
                            vTargetAngles[1] = TargetList[0]->GetAngle()[1];

                            Vector difference;
                            difference[0] = vTargetAngles[0] - vOldViewAngles[0];
                            difference[1] = vTargetAngles[1] - vOldViewAngles[1];
                            if (difference[0] < 0.0f) difference[0] *= -1.0f;
                            if (difference[1] < 0.0f) difference[1] *= -1.0f;

                            if (difference[0] >= 180.0f)
                            {
                              difference[0] = 360.0f - difference[0];
                              Vector vAngs;
                              g_pEngineClient->GetViewAngles(vAngs);
                              vAngs[0] += vTargetAngles[0] < vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                              g_pEngineClient->SetViewAngles(vAngs);
                              //pCMgr->m_pfCrossHairController[0] += vTargetAngles[0] < vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                              //pCmd->viewangles[0] += vTargetAngles[0] < vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                            }
                            else
                            {
                              Vector vAngs;
                              g_pEngineClient->GetViewAngles(vAngs);
                              vAngs[0] += vTargetAngles[0] > vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                              g_pEngineClient->SetViewAngles(vAngs);
                              //pCMgr->m_pfCrossHairController[0] += vTargetAngles[0] > vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                              //pCmd->viewangles[0] += vTargetAngles[0] > vOldViewAngles[0] ? difference[0] / (m_flShotgunsSmooth - i) : -(difference[0] / (m_flShotgunsSmooth - i));
                            }

                            if (difference[1] >= 180.0f)
                            {
                              difference[1] = 360.0f - difference[1];
                              Vector vAngs;
                              g_pEngineClient->GetViewAngles(vAngs);
                              vAngs[1] += vTargetAngles[1] < vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                              g_pEngineClient->SetViewAngles(vAngs);
                              //pCMgr->m_pfCrossHairController[1] += vTargetAngles[1] < vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                              //pCmd->viewangles[1] += vTargetAngles[1] < vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                            }
                            else
                            {
                              Vector vAngs;
                              g_pEngineClient->GetViewAngles(vAngs);
                              vAngs[1] += vTargetAngles[1] > vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                              g_pEngineClient->SetViewAngles(vAngs);
                              //pCMgr->m_pfCrossHairController[1] += vTargetAngles[1] > vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                              //pCmd->viewangles[1] += vTargetAngles[1] > vOldViewAngles[1] ? difference[1] / (m_flShotgunsSmooth - i) : -(difference[1] / (m_flShotgunsSmooth - i));
                            }

                            if (i + 1.0f >= m_flShotgunsSmooth)
                            {
                              TargetList[0]->CalculateAngleTo(m_pPlayer, GetBestBone(TargetList[0]));
                              Vector vAngs = { TargetList[0]->GetAngle()[0], TargetList[0]->GetAngle()[1], 0.0f };
                              g_pEngineClient->SetViewAngles(vAngs);
                              //pCMgr->m_pfCrossHairController[0] = TargetList[0]->GetAngle()[0];
                              //pCMgr->m_pfCrossHairController[1] = TargetList[0]->GetAngle()[1];
                              //pCmd->viewangles[0] = TargetList[0]->GetAngle()[0];
                              //pCmd->viewangles[1] = TargetList[0]->GetAngle()[1];

                              //pCmd->buttons |= IN_ATTACK;
                              //*pCMgr->m_piAttack_Status = ACTION_DO;
                              g_pEngineClient->ExecCMD(XS("+attack; wait 100; -attack"));
                              //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                              m_iTimeLastShoot = clock();

                              do
                              {
                                TargetList[0]->CalculateAngleTo(m_pPlayer, GetBestBone(TargetList[0]));
                              } while (clock() - m_iTimeLastShoot < 65 && TargetList[0]->IsAlive());

                              break;
                            }

                            this_thread::sleep_for(chrono::nanoseconds(1)); // 0.000001ms
                          }
                          m_bShooted = true;
                        }
                        else
                        {
                          Vector vTargetAngles;
                          vTargetAngles[0] = TargetList[0]->GetAngle()[0];
                          vTargetAngles[1] = TargetList[0]->GetAngle()[1];

                          g_pEngineClient->SetViewAngles(vTargetAngles);
                        }
                      }
                    }

                    if (!m_sActionAfterShoot.empty())
                    {
                      CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)actionAfterShoot, &m_iActionAfterShootTimer, NULL, NULL);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      if (!GetAsyncKeyState(m_iKeyCheatUse) || m_bSilent)
      {
        if (m_bShooted)
        {
          pCMgr->SendPacketStatus(true);
          m_bShooted = false;
        }
      }
    }
  }
}

bool C_CH_Aimbot::AutoWall(C_Player* target, int bone)
{
  //trace_t tr;
  //Ray_t ray;
  //Vector vStart, vEnd, vEndPos[3];
  //IClientEntity* pLocal = g_pEntList->GetClientEntity(g_pEngineClient->GetLocalPlayer());
  //vStart = pLocal->GetAbsOrigin() + pLocal->GetViewOffset();
  //float* flEnd = target->BonePos(bone);
  //vEnd[0] = flEnd[0];
  //vEnd[1] = flEnd[1];
  //vEnd[2] = flEnd[2];
  //CTraceFilter filter;

  //if (GameUtils::IsVisible(pLocal, pEntity, HitBox)) return true;

  //filter.pSkip = pLocal;
  //ray.Init(vStart, vEnd);

  //g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);
  //vEndPos[0] = tr.endpos;

  //ray.Init(vEnd, vStart);
  //filter.pSkip = pEntity;
  //g_pEngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_GRATE, &filter, &tr);
  //vEndPos[1] = tr.endpos;

  //VectorSubtract(vEndPos[0], vEndPos[1], vEndPos[2]);
  //return (vEndPos[2].Length() < 17.5f) ? true : false;
  return true;
}

void C_CH_Aimbot::FixSpread(C_Player* target)
{
  //CBasePlayer* pBase = (CBasePlayer*)m_pPlayer->BaseEntity();
  //CBaseCombatWeapon* curWeap = pBase->Weapon_GetSlot(1);
  //DWORD tempWeap = (DWORD)g_pEntList->GetClientEntityFromHandle(m_pPlayer->ActiveWeapon());
  //Vector spread = (Vector)(tempWeap + 0xC74);
  //QAngle finalAng;
  //VectorAngles(spread, finalAng);
  //pCmd->viewangles -= finalAng;

  //Vector vForward, vRight, vUp, vSpread, vNewAngles;
  ////QAngle qFinal;

  ////Utils::LimitAngles(pCmd->viewangles);

  //int iSeed = (pCmd->random_seed & 0x7fffffff) + 1;
  //pCMgr->RandomSeed(iSeed);

  //float flRandomX = pCMgr->RandomFloat(-0.5, 0.5) + pCMgr->RandomFloat(-0.5, 0.5);
  //float flRandomY = pCMgr->RandomFloat(-0.5, 0.5) + pCMgr->RandomFloat(-0.5, 0.5);

  //DWORD tempWeap = (DWORD)g_pIEntList->GetClientEntityFromHandle(m_pMyPlayer->ActiveWeapon());
  //float flSpread = *(float*)(tempWeap + 0xC74);
  //cout << "flSpread:: " << flSpread << endl;

  //vSpread.x = flRandomX * flSpread;
  //vSpread.y = flRandomY * flSpread;
  //vSpread.z = 0;
  //cout << "[" << vSpread.x << "] [" << vSpread.y << "]" << endl;
  //cout << "[" << pCmd->viewangles.x << "] [" << pCmd->viewangles.y << "]" << endl;

  //pCmd->viewangles[0] -= vSpread[0];
  //pCmd->viewangles[1] -= vSpread[1];

  //if (vSpread.x > 0)
  //  pCmd->viewangles.x = pCmd->viewangles.x - vSpread.x;
  //else
  //  pCmd->viewangles.x = pCmd->viewangles.x + vSpread.x;
  //if (vSpread.y > 0)
  //  pCmd->viewangles.y = pCmd->viewangles.y - vSpread.y;
  //else
  //  pCmd->viewangles.y = pCmd->viewangles.y + vSpread.y;

  //AngleVectors(pCmd->viewangles, &vForward, &vRight, &vUp);
  //cout << "[" << vForward.x << "] [" << vForward.y << "] [" << vForward.z << endl;

  //vNewAngles.x = vForward.x + (vRight.x * vSpread.x) + (vUp.x * vSpread.y);
  //vNewAngles.y = vForward.y + (vRight.y * vSpread.x) + (vUp.y * vSpread.y);
  //vNewAngles.z = vForward.z + (vRight.z * vSpread.x) + (vUp.z * vSpread.y);

  //vNewAngles = vForward + (vRight *  vSpread[0]) + (vUp * vSpread[1]);
  //vNewAngles.NormalizeInPlace();
  //VectorAngles(vNewAngles, qFinal);

  //Utils::LimitAngles(qFinal);

  //cout << pCmd->viewangles.x << " " << pCmd->viewangles.y << " " << pCmd->viewangles.z << endl;
  //cout << qFinal.x << " " << qFinal.y << " " << qFinal.z << endl;
  //pCmd->viewangles += pCmd->viewangles - qFinal;
}

bool C_CH_Aimbot::IsAbleToShoot()
{
  float flServerTime = (float)(m_pPlayer->TickBase() * g_pGlobalsClient->interval_per_tick);
  CBaseCombatWeapon* tempWeap = 0;
  tempWeap = (CBaseCombatWeapon*)g_pEntList->GetClientEntityFromHandle(m_pPlayer->ActiveWeapon());

  if (!tempWeap) return false;
  //float flNextPrimaryAttack = *(float*)(tempWeap + /*0x120*/0x8F8);
  float flNextPrimaryAttack = tempWeap->m_flNextPrimaryAttack;
  //bool InReload = *(PBOOL)(tempWeap + 0x955);
  bool InReload = tempWeap->m_bInReload;

  bool IsAbleToShoot = (flServerTime > flNextPrimaryAttack);
  if (IsAbleToShoot == false)
  {
    if (InReload)
    {
      IsAbleToShoot = true;
    }
    else
    {
      flNextPrimaryAttack = *(float*)((DWORD*)tempWeap + 0x120/*0x8F8*/);
      IsAbleToShoot = (flServerTime > flNextPrimaryAttack);
    }
  }
  return IsAbleToShoot;
}

DWORD C_CH_Aimbot::actionAfterShoot(LPVOID SleepTime)
{
  this_thread::sleep_for(chrono::milliseconds(*(int*)SleepTime));

  C_CH_Aimbot* aimbotCheat = ((C_CH_Aimbot*)C_CheatMgr::GetCheat(XS("C_CH_Aimbot")));

  static int time_last_action = clock();

  if (aimbotCheat != 0)
  {
    if (clock() - time_last_action > aimbotCheat->m_iActionAfterShootTimer)
    {
      if (!aimbotCheat->m_sActionAfterShoot.empty())
      {
        g_pEngineClient->ExecCMD(aimbotCheat->m_sActionAfterShoot.c_str());
      }
    }
  }
  ExitThread(0);
}

void C_CH_Aimbot::restoreChanges()
{

}
