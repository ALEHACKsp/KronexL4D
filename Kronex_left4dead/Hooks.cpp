#include "KronexMain.h"

void InitFont()
{
  static vgui::HFont hFont;
  static bool WasInited = false;
  if (!WasInited)
  {
    hFont = g_pSurface->CreateFont();
    g_pSurface->SetFontGlyphSet(hFont, XS("Arial"), 17, 10, 0, 0, vgui::ISurface::FONTFLAG_OUTLINE);
    WasInited = true;
  }
  g_pSurface->DrawSetTextFont(hFont);
}

bool __fastcall Hooks::CreateMoveNew(
  void* thisptr,
  void* pEdx,
  float flInputSampleTime,
  CUserCmd *cmd)
{
  return true;
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //BYTE* codeDest = (BYTE*)C_CheatMgr::Instance->g_OrigCreateMoveNew;
  //codeDest[0] = C_CheatMgr::Instance->g_codeFragment_p9[0];
  //*((DWORD*)(codeDest + 1)) = *((DWORD*)(C_CheatMgr::Instance->g_codeFragment_p9 + 1));

  //bool retStatus = C_CheatMgr::Instance->g_OrigCreateMoveNew(thisptr, flInputSampleTime, cmd);
  ///////////////////////////////////////////////////////////////////////////////////////////////

  //pCmd = cmd;

  //C_CH_BunnyHop* bhop = (C_CH_BunnyHop*)C_CheatMgr::Instance->GetCheat(XS("C_CH_BunnyHop"));
  //C_CH_Aimbot* aimbot = (C_CH_Aimbot*)C_CheatMgr::Instance->GetCheat(XS("C_CH_Aimbot"));

  //aimbot->oldView = cmd->viewangles;
  //float oldSidemove = cmd->sidemove;
  //float oldForwardmove = cmd->forwardmove;

  //if (aimbot)
  //{
  //  aimbot->update();
  //  if (aimbot->m_bIsCheatEnabled)
  //  {
  //    if (/*cmd->buttons & IN_ATTACK && */aimbot->IsAbleToShoot())
  //    {
  //      //g_pEngineClient->GetViewAngles(oldAngs);
  //      aimbot->perform();
  //    }
  //  }
  //}

  ////DWORD dwEBP = NULL;

  ////__asm MOV dwEBP, EBP;

  ////BYTE* bSendPacket = (BYTE*)(*((char**)dwEBP - 0x21));

  //if (cmd->buttons & IN_ATTACK && aimbot->IsAbleToShoot())
  //{
  //  //cout << "bSendPacket: " << hex << bSendPacket << endl;
  //  //*bSendPacket = false;
  //  C_CheatMgr::Instance->SendPacketStatus(false);
  //  //g_pEngineClient->SetViewAngles(oldAngs);
  //}
  //else
  //{
  //  //*bSendPacket = true;
  //  C_CheatMgr::Instance->SendPacketStatus(true);
  //  cmd->viewangles = aimbot->oldView;
  //  cmd->sidemove = oldSidemove;
  //  cmd->forwardmove = oldForwardmove;
  //  //g_pEngineClient->SetViewAngles(oldAngs);
  //}

  //C_CheatMgr::Instance->m_pfCrossHairController[0] = aimbot->oldView[0];
  //C_CheatMgr::Instance->m_pfCrossHairController[1] = aimbot->oldView[1];
  //C_CheatMgr::Instance->m_pfCrossHairController[2] = aimbot->oldView[2];

  //if (bhop)
  //{
  //  if (bhop->m_hPerformThread && bhop->m_hUpdateThread)
  //  {
  //    bhop->update();
  //    if (bhop->m_bIsCheatEnabled)
  //    {
  //      C_Player* pPlayer = bhop->m_pPlayer;
  //      if (pCmd->buttons & IN_JUMP)
  //      {
  //        if (bhop->m_pPlayer->Velocity(2) > 0.0f)
  //        {
  //          pCmd->buttons &= ~IN_DUCK;
  //        }
  //        if (bhop->m_pPlayer->Velocity(2) < 0.0f)
  //        {
  //          pCmd->buttons &= ~IN_JUMP;

  //          if ((pPlayer->Team() == TEAM_SURV && Utils::Get2dSummaryVelocity(pPlayer->Velocity(0), pPlayer->Velocity(1)) > 220.0f)
  //            || (pPlayer->Team() == TEAM_INFECT && Utils::Get2dSummaryVelocity(pPlayer->Velocity(0), pPlayer->Velocity(1)) > 150.0f))
  //          {
  //            pCmd->buttons |= IN_DUCK;
  //          }
  //        }
  //        if (bhop->m_pPlayer->Velocity(2) == 0.0f)
  //        {
  //          C_CheatMgr::Instance->SendPacketStatus(true);
  //          pCmd->buttons &= ~IN_DUCK;
  //        }
  //      }
  //    }
  //  }
  //}

  //codeDest = (BYTE*)C_CheatMgr::Instance->g_OrigCreateMoveNew;
  //codeDest[0] = C_CheatMgr::Instance->g_jmp_p9[0];
  //*((DWORD*)(codeDest + 1)) = *((DWORD*)(C_CheatMgr::Instance->g_jmp_p9 + 1));

  //return retStatus;
}

void __fastcall Hooks::IBaseClientDLL_CreateMove(
  IBaseClientDLL* thisptr,
  void* pEdx,
  int sequence_number,
  float input_sample_frametime,
  bool active)
{
  C_VMTHookMgr::GetHook(XS("IBaseClientDLL_CreateMove"))->GetOriginFn<CreateMoveFn>()(thisptr, sequence_number, input_sample_frametime, active);

  if (sequence_number == 0) return;

  pCmd = C_CheatMgr::Instance->pUserCmds[sequence_number % 150];
  
  C_CH_BunnyHop* bhop = (C_CH_BunnyHop*)C_CheatMgr::Instance->GetCheat(XS("C_CH_BunnyHop"));
  //C_CH_Aimbot* aimbot = (C_CH_Aimbot*)C_CheatMgr::Instance->GetCheat(XS("C_CH_Aimbot"));

  if (bhop)
  {
    bhop->update();
    if (bhop->m_bIsCheatEnabled)
    {
      bhop->perform();
    }
  }

  //if (aimbot)
  //{
  //  aimbot->update();
  //  if (aimbot->m_bIsCheatEnabled)
  //  {
  //    aimbot->perform();
  //  }
  //}

  //static int last_shoot = clock();
  //static bool bSendPacket = true;

  //if (clock() - last_shoot < 200)
  //{
  //  if (bSendPacket)
  //  {
  //    C_CheatMgr::Instance->SendPacketStatus(false);
  //    bSendPacket = false;
  //  }
  //}
  //else
  //{
  //  if (!bSendPacket)
  //  {
  //    C_CheatMgr::Instance->SendPacketStatus(true);
  //    bSendPacket = true;
  //  }
  //}

  //QAngle oldView = pCmd->viewangles;
  //float oldSidemove = pCmd->sidemove;
  //float oldForwardmove = pCmd->forwardmove;

  //if (aimbot && clock() - last_shoot > 500)
  //{
  //  if (pCmd->buttons & IN_ATTACK)
  //  {
  //    aimbot->update();
  //    aimbot->perform();
  //    //last_shoot = clock();

  //    //static int choke_counter;

  //    //if (!active) choke_counter++;
  //    //if (choke_counter > 6)
  //    //{
  //    //  active = true;
  //    //  choke_counter = 0;
  //    //  cout << "choked" << endl;
  //    //}
  //  }
  //}

  //if (pCmd->buttons & IN_ATTACK && aimbot && clock() - last_shoot > 500)
  //{
  //  C_CheatMgr::Instance->SendPacketStatus(false);
  //  last_shoot = clock();
  //}
  //else
  //{
  //  C_CheatMgr::Instance->SendPacketStatus(true);
  //  pCmd->viewangles = oldView;
  //  pCmd->sidemove = oldSidemove;
  //  pCmd->forwardmove = oldForwardmove;
  //}

}

void DrawKronexTitle()
{
  if (!g_pEngineClient->IsTakingScreenshot())
  {
    InitFont();

    int scr_X, scr_Y;
    g_pEngineClient->GetScreenSize(scr_X, scr_Y);
    g_pSurface->DrawSetTextColor(255, 0, 0, 255);
    g_pSurface->DrawSetTextPos((float)scr_X / (float)100 * (float)70, (float)scr_Y / (float)100 * (float)95);
    Utils::DrawPrintText(XS("Left 4 Dead KronexHook by Astarion"));
  }
}

void DrawCrossHair()
{
  if (!g_pEngineClient->IsTakingScreenshot())
  {
    int scr_X, scr_Y;
    g_pEngineClient->GetScreenSize(scr_X, scr_Y);
    int size = scr_Y / 50;
    g_pSurface->DrawSetColor(255, 0, 0, 255);
    g_pSurface->DrawLine(scr_X / 2 - size, scr_Y / 2, scr_X / 2 + size, scr_Y / 2); // crosshair horizontal
    g_pSurface->DrawLine(scr_X / 2, scr_Y / 2 - size, scr_X / 2, scr_Y / 2 + size); // crosshair vertical

    size /= 3;
    g_pSurface->DrawSetColor(255, 255, 255, 255);
    g_pSurface->DrawLine(scr_X / 2 - size, scr_Y / 2, scr_X / 2 + size, scr_Y / 2); // crosshair horizontal
    g_pSurface->DrawLine(scr_X / 2, scr_Y / 2 - size, scr_X / 2, scr_Y / 2 + size); // crosshair vertical
  }
  //g_pSurface->DrawSetColor(0, 255, 255, 255); // square color
  //g_pSurface->DrawOutlinedRect(scr_X / 2 - size / 2, scr_Y / 2 - size / 2, scr_X / 2 + size / 2 + 1, scr_Y / 2 + size / 2 + 1); // square
}

void DrawESP()
{
  if (!g_pEngineClient->IsTakingScreenshot())
  {
    InitFont();

    int boneID = 10;

    C_CH_ESP* espCheat = ((C_CH_ESP*)C_CheatMgr::GetCheat(XS("C_CH_ESP")));

    if (espCheat)
    {
      if (IS_EXEC_ALLOWED)
      {
        if (espCheat->m_bIsCheatEnabled)
        {
          C_Player* pPlayer = espCheat->m_pPlayer;

          if (espCheat->findTargets())
          {
            int targetsCount = espCheat->TargetList.size();
            for (int iterator = 0; iterator < targetsCount; iterator++)
            {
              C_Player* target = espCheat->TargetList[iterator];

              if (target)
              {
                if (espCheat->PlayerBoneToScreen(target, boneID))
                {
                  g_pSurface->DrawSetColor(espCheat->GetColor(target));

                  float chartype_width_factor = 1.0f;
                  float chartype_height_factor = 1.0f;
                  float distance = Utils::Get3dDistance(pPlayer->Position(), target->BonePos(boneID));

                  switch (target->CharType())
                  {
                    case CHARACTER_TYPE_BOOMER: { chartype_width_factor = 19.0f; chartype_height_factor = 0.9f; break; }
                    case CHARACTER_TYPE_HUNTER: { chartype_width_factor = 15.0f; chartype_height_factor = 0.7f; break; }
                    case CHARACTER_TYPE_SMOKER: { chartype_width_factor = 15.0f; chartype_height_factor = 1.0f; break; }
                    case CHARACTER_TYPE_TANK: { chartype_width_factor = 30.0f; chartype_height_factor = 1.0f; break; }
                    default: { chartype_width_factor = 20.0f; chartype_height_factor = 0.8f; break; }
                  }

                  int x = (int)(target->vBonePos[boneID].x);
                  int y = (int)(target->vBonePos[boneID].y);

                  int width = (int)(espCheat->m_iScreen_X * chartype_width_factor / distance);
                  int height = (int)(target->YDiff() * espCheat->m_iScreen_Y * chartype_height_factor / distance);

                  if (espCheat->m_bDrawESPBox)
                  {
                    Utils::DrawOutlinedRect(x - (width / 2),
                      y - (height / 2),
                      x + (width / 2),
                      y + (height / 2),
                      espCheat->m_iBoxThickness);
                  }

                  if (espCheat->m_bDrawSnapLine/* && i == 0*/)
                  {
                    Utils::DrawLine(espCheat->m_iScreen_X / 2, espCheat->m_iScreen_Y,
                      espCheat->TargetList[iterator]->vBonePos[boneID].x,
                      espCheat->TargetList[iterator]->vBonePos[boneID].y, espCheat->m_iSnapLineThickness);
                  }

                  if (espCheat->m_bDrawSkeleton)
                  {
                    for (int i = 0; i < 4; i++)
                    {
                      if (espCheat->PlayerBoneToScreen(target, i))
                      {
                        if (espCheat->PlayerBoneToScreen(target, i + 1))
                        {
                          Utils::DrawLine(
                            target->vBonePos[i].x,
                            target->vBonePos[i].y,
                            target->vBonePos[i + 1].x,
                            target->vBonePos[i + 1].y,
                            espCheat->m_iSkeletonThickness);
                        }
                      }
                    }
                    if (espCheat->PlayerBoneToScreen(target, 0))
                    {
                      if (espCheat->PlayerBoneToScreen(target, 5))
                      {
                        Utils::DrawLine(target->vBonePos[0].x,
                          target->vBonePos[0].y,
                          target->vBonePos[5].x,
                          target->vBonePos[5].y,
                          espCheat->m_iSkeletonThickness);
                      }
                    }
                    for (int i = 5; i < 8; i++)
                    {
                      if (espCheat->PlayerBoneToScreen(target, i))
                      {
                        if (espCheat->PlayerBoneToScreen(target, i + 1))
                        {
                          Utils::DrawLine(target->vBonePos[i].x,
                            target->vBonePos[i].y,
                            target->vBonePos[i + 1].x,
                            target->vBonePos[i + 1].y,
                            espCheat->m_iSkeletonThickness);
                        }
                      }
                    }
                    if (espCheat->PlayerBoneToScreen(target, 0))
                    {
                      if (espCheat->PlayerBoneToScreen(target, 9))
                      {
                        Utils::DrawLine(target->vBonePos[0].x,
                          target->vBonePos[0].y,
                          target->vBonePos[9].x,
                          target->vBonePos[9].y,
                          espCheat->m_iSkeletonThickness);
                      }
                    }
                    for (int i = 9; i < 12; i++)
                    {
                      if (espCheat->PlayerBoneToScreen(target, i))
                      {
                        if (espCheat->PlayerBoneToScreen(target, i + 1))
                        {
                          Utils::DrawLine(target->vBonePos[i].x,
                            target->vBonePos[i].y,
                            target->vBonePos[i + 1].x,
                            target->vBonePos[i + 1].y,
                            espCheat->m_iSkeletonThickness);
                        }
                      }
                    }
                    //if (WorldToScreen(target->BonePos(14), Point1))
                    //{
                    //  if (WorldToScreen(target->BonePos(14), Point2))
                    //  {
                    //    DrawFilledRect((int)target->flPosScreen_X - m_Rect.left, (int)target->flPosScreen_Y - m_Rect.top, 10, 10, RGB(255, 0, 0));
                    //  }
                    //}
                    //if (WorldToScreen(target->BonePos(13), Point1))
                    //{
                    //  if (WorldToScreen(target->BonePos(16), Point2))
                    //  {
                    //    DrawLine((int)target->flPosScreen_X - m_Rect.left, (int)target->flPosScreen_Y - m_Rect.top, (int)Point2[0] - m_Rect.left, (int)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor);
                    //  }
                    //}
                    for (int i = 16; i < 18; i++)
                    {
                      if (espCheat->PlayerBoneToScreen(target, i))
                      {
                        if (espCheat->PlayerBoneToScreen(target, i + 1))
                        {
                          Utils::DrawLine(target->vBonePos[i].x,
                            target->vBonePos[i].y,
                            target->vBonePos[i + 1].x,
                            target->vBonePos[i + 1].y,
                            espCheat->m_iSkeletonThickness);
                        }
                      }
                    }
                    if (target->CharType() == CHARACTER_TYPE_BOOMER
                        || target->CharType() == CHARACTER_TYPE_SMOKER)
                    {
                      //if (WorldToScreen(target->BonePos(13), Point1))
                      //{
                      //  if (WorldToScreen(target->BonePos(20), Point2))
                      //  {
                      //    DrawLine((int)target->flPosScreen_X - m_Rect.left, (int)target->flPosScreen_Y - m_Rect.top, (int)Point2[0] - m_Rect.left, (int)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor);
                      //  }
                      //}
                      for (int i = 20; i < 22; i++)
                      {
                        if (espCheat->PlayerBoneToScreen(target, i))
                        {
                          if (espCheat->PlayerBoneToScreen(target, i + 1))
                          {
                            Utils::DrawLine(target->vBonePos[i].x,
                              target->vBonePos[i].y,
                              target->vBonePos[i + 1].x,
                              target->vBonePos[i + 1].y,
                              espCheat->m_iSkeletonThickness);
                          }
                        }
                      }
                    }
                    else
                    {
                      //if (WorldToScreen(target->BonePos(13), Point1))
                      //{
                      //  if (WorldToScreen(target->BonePos(35), Point2))
                      //  {
                      //    DrawLine((int)target->flPosScreen_X - m_Rect.left, (int)target->flPosScreen_Y - m_Rect.top, (int)Point2[0] - m_Rect.left, (int)Point2[1] - m_Rect.top, m_iSkeletonThickness, espColor);
                      //  }
                      //}
                      for (int i = 35; i < 37; i++)
                      {
                        if (espCheat->PlayerBoneToScreen(target, i))
                        {
                          if (espCheat->PlayerBoneToScreen(target, i + 1))
                          {
                            Utils::DrawLine(target->vBonePos[i].x,
                              target->vBonePos[i].y,
                              target->vBonePos[i + 1].x,
                              target->vBonePos[i + 1].y,
                              espCheat->m_iSkeletonThickness);
                          }
                        }
                      }
                    }
                  }

                  if (espCheat->m_bDrawHealthVisual)
                  {
                    int indentationFromBox = 2;

                    int pixels_dead = height - (int)((float)height * ((float)target->Health() / (float)target->MaxHealth()));

                    g_pSurface->DrawSetColor(255, 0, 0, 255);
                    g_pSurface->DrawFilledRect(x - (width / 2) - indentationFromBox - espCheat->m_iBoxThickness,
                      y - (height / 2),
                      x - (width / 2) - indentationFromBox,
                      y - (height / 2) + pixels_dead);

                    g_pSurface->DrawSetColor(0, 255, 0, 255);
                    g_pSurface->DrawFilledRect(x - (width / 2) - indentationFromBox - espCheat->m_iBoxThickness,
                      y - (height / 2) + pixels_dead,
                      x - (width / 2) - indentationFromBox,
                      y + (height / 2));
                  }

                  if (espCheat->m_bDrawHealth)
                  {
                    g_pSurface->DrawSetTextColor(
                      espCheat->m_iTextColor_R,
                      espCheat->m_iTextColor_G,
                      espCheat->m_iTextColor_B, 255);
                    g_pSurface->DrawSetTextPos(x - (width / 4), y - (height / 2) - 20);

                    Utils::DrawPrintText(to_string(target->Health()));
                  }

                  if (espCheat->m_bDrawTankFrustration && target->CharType() == CHARACTER_TYPE_TANK)
                  {
                    g_pSurface->DrawSetTextColor(
                      espCheat->m_iTextColor_R,
                      espCheat->m_iTextColor_G,
                      espCheat->m_iTextColor_B, 255);
                    g_pSurface->DrawSetTextPos(x - (width / 4), y - (height / 2) - 40);

                    Utils::DrawPrintText(XS("TANK: ") + to_string(target->TankFrustration()) + XS("%"));
                  }

                  if (espCheat->m_bDrawNickName)
                  {
                    g_pSurface->DrawSetTextColor(
                      espCheat->m_iTextColor_R,
                      espCheat->m_iTextColor_G,
                      espCheat->m_iTextColor_B, 255);
                    g_pSurface->DrawSetTextPos(x - (width / 4), y + (height / 2) + 5);

                    Utils::DrawPrintText(target->Nickname());
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void SpecChecker()
{
  C_EntityMgr eMgr;

  vector<C_Player*> vObservers;
  CBaseHandle hObserverTarget;
  IClientEntity* pClientEntity;

  //static DWORD UI_Font = g_pSurface->CreateFont();

  //g_pSurface->SetFontGlyphSet(UI_Font, XS("Arial"), 13, 250, 0, 0, 0x200);
  //g_pSurface->DrawSetTextColor(255, 0, 0, 255);
  //g_pSurface->DrawSetTextFont(UI_Font);

  C_Player* player;
  int playerCount = eMgr.EntityList.size();
  for (int i = 0; i < playerCount; i++)
  {
    player = eMgr.EntityList[i];

    hObserverTarget = player->ObserverTarget();
    //if (hObserverTarget)
    {
      pClientEntity = g_pEntList->GetClientEntityFromHandle(hObserverTarget);
      CBaseEntity* ent = (CBaseEntity*)pClientEntity->GetBaseEntity();
      ent->ChangeTeam(3);
      if (pClientEntity)
      {
        if (eMgr.EntityList[g_pEngineClient->GetLocalPlayer()]->m_dwBase == (DWORD)pClientEntity)
        {
          vObservers.push_back(player);

          //g_pSurface->DrawSetTextPos(10, 5);
          //g_pSurface->DrawPrintText(player->Nickname(), (int)wcslen(text));
        }
      }
    }
  }
}

void RadarHack()
{
  if (!g_pEngineClient->IsTakingScreenshot())
  {
    InitFont();

    int scr_X, scr_Y;
    g_pEngineClient->GetScreenSize(scr_X, scr_Y);

    int iStart_X = 70;
    int iStart_Y = 70;
    int iDrawRadius = 50;
    float flRange = 500;
    int iSegments = 10;

    C_CheatMgr* pCMgr = C_CheatMgr::Instance;
    C_CH_Radar* pRadar = (C_CH_Radar*)pCMgr->GetCheat(XS("C_CH_Radar"));

    if (pRadar)
    {
      iStart_X = pRadar->m_iPos_X;
      iStart_Y = pRadar->m_iPos_Y;
      iDrawRadius = pRadar->m_iDrawRadius;
      flRange = pRadar->m_flRange;
      iSegments = pRadar->m_iSegments;

      if (pRadar->m_bIsCheatEnabled)
      {
        g_pSurface->DrawSetColor(255, 0, 0, 255);
        g_pSurface->DrawOutlinedCircle(iStart_X, iStart_Y, iDrawRadius, iSegments);

        float fov = 45.0f;

        fov = C_CVarMgr::FindVar(XS("cl_fov"))->GetFloat() / 2.0f;

        if (pRadar->m_bDrawFovBackGround)
        {
          g_pSurface->DrawSetColor(210, 210, 210, 20);
          for (int i = -(int)fov; i < (int)fov; i++)
          {
            Utils::DrawLine(iStart_X, iStart_Y, iStart_X + iDrawRadius * sinf(DEG_TO_RAD(i)), iStart_Y - iDrawRadius * cosf(DEG_TO_RAD(i)), 2);
          }
        }

        if (pRadar->m_bDrawFovLines)
        {
          g_pSurface->DrawSetColor(255, 0, 0, 255);
          g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X - iDrawRadius * sinf(DEG_TO_RAD(fov)), iStart_Y - iDrawRadius * cosf(DEG_TO_RAD(fov)));
          g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X + iDrawRadius * sinf(DEG_TO_RAD(fov)), iStart_Y - iDrawRadius * cosf(DEG_TO_RAD(fov)));
          g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X, iStart_Y - iDrawRadius);

          C_CH_Aimbot* pAimbot = (C_CH_Aimbot*)pCMgr->GetCheat(XS("C_CH_Aimbot"));
          if (pAimbot)
          {
            if (pAimbot->m_bIsCheatEnabled)
            {
              fov = pAimbot->m_flFOV;

              g_pSurface->DrawSetColor(255, 0, 0, 255);
              g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X - iDrawRadius * sinf(DEG_TO_RAD(fov)), iStart_Y - iDrawRadius * cosf(DEG_TO_RAD(fov)));
              g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X + iDrawRadius * sinf(DEG_TO_RAD(fov)), iStart_Y - iDrawRadius * cosf(DEG_TO_RAD(fov)));
              g_pSurface->DrawLine(iStart_X, iStart_Y, iStart_X, iStart_Y - iDrawRadius);
            }
          }
        }

        if (pRadar->findTargets())
        {
          vector<C_Player*> targetList = pRadar->TargetList;

          C_Player* pPlayer = pRadar->m_pPlayer;

          if (pPlayer)
          {
            float* MyPos = pPlayer->Position();

            for (int i = 0; i < (int)targetList.size(); i++)
            {
              C_Player* target = targetList[i];
              if (target)
              {
                float* targetPos = target->Position();

                if (Utils::Get2dDistance(MyPos, targetPos) < flRange - (flRange / (float)iDrawRadius))
                {
                  float angle_x = pCmd->viewangles[1];

                  float x_diff = (MyPos[1] - targetPos[1]) / (flRange / (float)iDrawRadius) * cosf(DEG_TO_RAD(angle_x)) + (MyPos[0] - targetPos[0]) / (flRange / (float)iDrawRadius) * -sinf(DEG_TO_RAD(angle_x)); // +5
                  float y_diff = (MyPos[0] - targetPos[0]) / (flRange / (float)iDrawRadius) * cosf(DEG_TO_RAD(angle_x)) + (MyPos[1] - targetPos[1]) / (flRange / (float)iDrawRadius) * sinf(DEG_TO_RAD(angle_x)); // -5
                  
                  g_pSurface->DrawSetColor(pRadar->GetColor(target));
                  Utils::DrawFilledCircle((iStart_X + x_diff), (iStart_Y + y_diff), pRadar->m_iPointSize, pRadar->m_iPointSegments);
                }
              }
            }
          }
        }
      }
    }
  }
}

void __fastcall Hooks::IPanel_PaintTraverse(
  vgui::IPanel* pIPanel,
  void* pEdx,
  unsigned int VGUIPanel,
  bool forcerepaint,
  bool allowforce)
{
  const char* szName = g_pPanel->GetPanelClassName(VGUIPanel);

  //cout << szName << endl;

  if (szName[0] == 'M' && szName[3] == 'S' // MatSystemTopPanel
      || szName[0] == 'F' && szName[5] == 'O' // FocusOverlayPanel
      || (szName[0] == 'G' && szName[4] == 'U') // GameUI Panel
    ) 
  {
    DrawKronexTitle();
    DrawCrossHair();
    DrawESP();
    RadarHack();
    //SpecChecker();
  }

  return C_VMTHookMgr::GetHook(XS("IPanel_PaintTraverse"))->GetOriginFn<PaintTraverseFn>()(pIPanel, VGUIPanel, forcerepaint, allowforce);
}

void __fastcall Hooks::IGameMovement_ProcessMovement(
  IGameMovement* thisptr,
  void* pEdx,
  CBasePlayer* pPlayer,
  CMoveData* pMove)
{
  C_VMTHookMgr::GetHook(XS("IGameMovement_ProcessMovement"))->GetOriginFn<ProcessMovementFn>()(thisptr, pPlayer, pMove);


  //cout << pMove->m_vecAngles[0] << " " << pMove->m_vecAngles[1] << endl;

  //return C_VMTHookMgr::GetHook(XS("IGameMovement_ProcessMovement"))->GetOriginFn<ProcessMovementFn>()(thisptr, pPlayer, pMove);
}

void __fastcall Hooks::IPrediction_SetupMove(
  IPrediction* thisptr,
  void* pEdx,
  C_BasePlayer *player,
  CUserCmd *ucmd,
  IMoveHelper *pHelper,
  CMoveData *move)
{
  C_VMTHookMgr::GetHook(XS("IPrediction_SetupMove"))->GetOriginFn<SetupMoveFn>()(thisptr, player, ucmd, pHelper, move);


}

void __fastcall Hooks::IPrediction_FinishMove(
  IPrediction* thisptr,
  void* pEdx,
  C_BasePlayer *player,
  CUserCmd *ucmd,
  CMoveData *move)
{
  C_VMTHookMgr::GetHook(XS("IPrediction_FinishMove"))->GetOriginFn<FinishMoveFn>()(thisptr, player, ucmd, move);


}

void __fastcall Hooks::IEngineTrace_TraceRay(
  IEngineTrace* thisptr,
  void* pEdx,
  const Ray_t &ray,
  unsigned int fMask,
  ITraceFilter *pTraceFilter,
  trace_t *pTrace)
{
  C_VMTHookMgr::GetHook(XS("IEngineTrace_TraceRay"))->GetOriginFn<TraceRayFn>()(thisptr, ray, fMask, pTraceFilter, pTrace);


}

int __fastcall Hooks::IVModelRender_DrawModel(
  IVModelRender* thisptr,
  void* pEdx,
  int flags,
  IClientRenderable *pRenderable,
  ModelInstanceHandle_t instance,
  int entity_index,
  const model_t *model,
  Vector const &origin,
  QAngle const &angles,
  int skin,
  int body,
  int hitboxset,
  const matrix3x4_t *modelToWorld,
  const matrix3x4_t *pLightingOffset)
{
  //_asm { pushad }

  //C_VMTHookMgr::GetHook(XS("IVModelRender_DrawModel"))->GetOriginFn<DrawModelFn>()(
  //  thisptr,
  //  flags,
  //  pRenderable,
  //  instance,
  //  entity_index,
  //  model,
  //  origin,
  //  angles,
  //  skin,
  //  body,
  //  hitboxset,
  //  modelToWorld,
  //  pLightingOffset);

  //_asm { popad }

  cout << "entity_index: " << dec << entity_index << endl;

  //IMaterial* pWitchMat = g_pMaterialSystem->FindMaterial(XS("\\models\\infected\\witch\\witch"), XS(TEXTURE_GROUP_MODEL));
  //if (pWitchMat)
  //{
  //  cout << "here!" << endl;
  //  pWitchMat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
  //}
  return 1;

  //return C_VMTHookMgr::GetHook(XS("IVModelRender_DrawModel"))->GetOriginFn<DrawModelFn>()(
  //  thisptr,
  //  flags,
  //  pRenderable,
  //  instance,
  //  entity_index,
  //  model,
  //  origin,
  //  angles,
  //  skin,
  //  body,
  //  hitboxset,
  //  modelToWorld,
  //  pLightingOffset);
}

void __fastcall Hooks::IVModelRender_DrawModelExecute(
  IVModelRender* thisptr,
  void* pEdx,
  const DrawModelState_t &state,
  const ModelRenderInfo_t &pInfo,
  matrix3x4_t *pCustomBoneToWorld)
{
  if (pInfo.pModel)
  {
    string pszModelName = g_pModelInfo->GetModelName(pInfo.pModel);
    if (pszModelName.find("models/player") != string::npos) // we left off here last snippet
    {
      // Max studio skins value is 32 found in studio.h. 
      // This is our array of material pointers.
      IMaterial *mats[MAXSTUDIOSKINS];
      // Here we are getting the studio model for our model 
      // using GetStudiomodel (index 29 of IVModelInfo).
      // We are going to use it to iterate through the model's materials.
      studiohdr_t* hdr = g_pModelInfo->GetStudiomodel(pInfo.pModel);
      //Drawing::Clr col, col2; // just some colors teehee
      // Here we are getting the Entity pointer as I mentioned at the start (thank you Based God!)
      CBaseEntity* pModelEntity = (CBaseEntity*)g_pEntList->GetClientEntity(pInfo.entity_index);
      if (pModelEntity) // just a checkle
      {
        // Getting the local player so we can check teams
        CBaseEntity* local = (CBaseEntity*)g_pEntList->GetClientEntity(g_pEngineClient->GetLocalPlayer());
        if (local) // just another checkle
        {
          // Another two checkles to check if the entity is alive (we don't want
          // to see bodies through walls, at least I dont). And a team check so
          // we don't see team mates through walls.
          if (pModelEntity->GetHealth() >= 1/* && pModelEntity->GetTeam() != local->GetTeam()*/)
          {
            g_pModelInfo->GetModelMaterials(pInfo.pModel, hdr->numtextures, mats);
            for (int i = 0; i < hdr->numtextures; i++)
            {
              IMaterial* mat = mats[i];
              if (!mat)
                continue;
              // Here we use SetMaterialVarFlag from the IMaterial class (31st index)
              mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
              mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
              mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
              mat->AlphaModulate(1.0f); // don't need this, I just use it just cause.

              float color1 = 0.5;
              // Here is your homework. Find the g_pRenderView class
              g_pRender->SetColorModulation(&color1);
              // Call to our original DrawModelExecute (we could juat as easily call oDrawModelExecute).
              // We call the original so we can have different colors based on visibility
              g_pModelRender->DrawModelExecute(state, pInfo, pCustomBoneToWorld);

              mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
              mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
              mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
              mat->AlphaModulate(1.0f);

              float color2 = 0.5;
              g_pRender->SetColorModulation(&color2);
            }
          }
          else // The else clause for if the model is not alive or on our team
          {   // Basically all this does is do what DrawModelExecute normally does to draw our regular legit models.
            g_pModelInfo->GetModelMaterials(pInfo.pModel, hdr->numtextures, mats);
            for (int i = 0; i < hdr->numtextures; i++)
            {
              IMaterial* mat = mats[i];
              if (!mat)
                continue;

              mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
              mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, false);
              mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
            }
          }
        }
      }
    }
  }



  C_VMTHookMgr::GetHook(XS("IVModelRender_DrawModelExecute"))->GetOriginFn<DrawModelExecuteFn>()(
    thisptr,
    state,
    pInfo,
    pCustomBoneToWorld);
  thisptr->ForcedMaterialOverride(NULL);
}