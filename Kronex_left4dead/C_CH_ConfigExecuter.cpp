#include "KronexMain.h"

C_CH_ConfigExecuter::C_CH_ConfigExecuter(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  C_CVarMgr::RegConVar(XS("krx_cfgexec_enabled"), XS("1"), FCVAR_SERVER_CAN_EXECUTE | FCVAR_HIDDEN);

  ReadConfigFile(XS("autoexec.cfg"));
  ReadConfigFile(XS("kronex.cfg"));

  m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_cfgexec_enabled"))->GetInt() == 1 ? true : false;

  m_iPerformSleepTime = 1000;

  if (m_bIsCheatEnabled)
  {
    //ConVar* pSvCheats = C_CVarMgr::FindVar(XS("sv_cheats"));
    //if (pSvCheats) pSvCheats->SetValue(XS("1"));

    g_pEngineClient->ExecCMD(XS("r_sse2 \"1\""));

    g_pEngineClient->ExecCMD(XS("rate \"166000\""));
    g_pEngineClient->ExecCMD(XS("cl_timeout \"60\""));
    g_pEngineClient->ExecCMD(XS("cl_resend \"3.5\""));

    g_pEngineClient->ExecCMD(XS("cl_updaterate \"165\""));
    g_pEngineClient->ExecCMD(XS("cl_cmdrate \"100\""));
    g_pEngineClient->ExecCMD(XS("cl_interp_ratio \"0\""));
    g_pEngineClient->ExecCMD(XS("cl_interp \"0\"")); // 0.00011
    g_pEngineClient->ExecCMD(XS("cl_lagcompensation \"1\""));

    g_pEngineClient->ExecCMD(XS("nb_update_frequency \"0.016\""));

    g_pEngineClient->ExecCMD(XS("net_maxroutable \"1200\""));
    g_pEngineClient->ExecCMD(XS("net_maxfragments \"1200\""));
    g_pEngineClient->ExecCMD(XS("net_splitrate \"3\""));
    g_pEngineClient->ExecCMD(XS("net_splitpacket_maxrate \"30000\""));

    g_pEngineClient->ExecCMD(XS("closecaption \"0\""));

    g_pEngineClient->ExecCMD(XS("cl_downloadfilter \"all\""));
    g_pEngineClient->ExecCMD(XS("cl_forcepreload \"1\""));
    g_pEngineClient->ExecCMD(XS("cl_ragdoll_limit \"0\""));
    g_pEngineClient->ExecCMD(XS("con_enable \"1\""));
    g_pEngineClient->ExecCMD(XS("dsp_enhance_stereo \"1\""));
    g_pEngineClient->ExecCMD(XS("func_break_max_pieces \"0\""));
    g_pEngineClient->ExecCMD(XS("mat_monitorgamma_tv_enabled \"1.0\""));
    g_pEngineClient->ExecCMD(XS("mat_grain_scale_override \"0.0\""));
    g_pEngineClient->ExecCMD(XS("spec_allowroaming \"1\""));

    g_pEngineClient->ExecCMD(XS("cl_autohelp \"0\""));
    g_pEngineClient->ExecCMD(XS("cl_predict \"1\""));
    g_pEngineClient->ExecCMD(XS("fps_max \"165.8\""));
    g_pEngineClient->ExecCMD(XS("gameinstructor_enable \"0\""));
    g_pEngineClient->ExecCMD(XS("cl_hidemenu_spawnmode \"5\""));
    g_pEngineClient->ExecCMD(XS("cl_hidemenu_spawnclass_hunter \"5\""));
    g_pEngineClient->ExecCMD(XS("cl_hidemenu_spawnclass_smoker \"5\""));
    g_pEngineClient->ExecCMD(XS("cl_hidemenu_spawnclass_boomer \"5\""));

    g_pEngineClient->ExecCMD(XS("sk_autoaim_mode \"2\""));

    g_pEngineClient->ExecCMD(XS("m_rawinput 1"));
    g_pEngineClient->ExecCMD(XS("m_filter 0"));
    g_pEngineClient->ExecCMD(XS("m_filter2 0"));
    g_pEngineClient->ExecCMD(XS("m_mouseaccel1 0"));
    g_pEngineClient->ExecCMD(XS("m_mouseaccel2 0"));
    g_pEngineClient->ExecCMD(XS("m_customaccel 0"));
    g_pEngineClient->ExecCMD(XS("m_mousespeed 0"));

    g_pEngineClient->ExecCMD(XS("cl_predictweapons \"0\""));
    g_pEngineClient->ExecCMD(XS("cl_threaded_bone_setup \"1\""));

    g_pEngineClient->ExecCMD(XS("z_gun_survivor_friend_push \"0\""));

    g_pEngineClient->ExecCMD(XS("echo Kronex Configuration for Left 4 Dead was loaded!"));
  }

  m_bIsCheatInitialized = true;
}

C_CH_ConfigExecuter::~C_CH_ConfigExecuter()
{
  C_CVarMgr::UnRegConVar(XS("krx_cfgexec_enabled"));
}

void C_CH_ConfigExecuter::update()
{
  //m_bIsCheatEnabled = C_CVarMgr::FindVar(XS("krx_cfgexec_enabled"))->GetInt() == 1 ? true : false;
}

void C_CH_ConfigExecuter::perform()
{
  
}

void C_CH_ConfigExecuter::restoreChanges()
{

}

void C_CH_ConfigExecuter::ReadConfigFile(const string &fileName)
{
  string execString = XS("exec ") + fileName;
  g_pEngineClient->ExecCMD(execString.c_str());
}
