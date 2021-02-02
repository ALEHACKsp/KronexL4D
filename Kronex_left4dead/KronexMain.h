#pragma once

// namespaces
using namespace std;

#pragma warning (disable: 4238)

// classes
class ICvar;
class IClientEntityList;
class CGlobalVarsBase;
class CUserCmd;
class C_CheatMgr;
class C_EntityMgr;
class C_PatchMgr;
class C_VMTHookMgr;
class C_CVarMgr;
class C_Player;
class C_Cheat;
class C_Patch;
class C_VMTHook;
class C_CH_Aimbot;
class C_CH_AutoRespInSurv;
class C_CH_BunnyHop;
class C_CH_Ceiling;
class C_CH_ESP;
class C_CH_Radar;
class C_CH_FakeLag;
class C_CH_NoRecoil;
class C_CH_LicenseChecker;
class C_CH_MaterialHack;
class C_CH_ConfigExecuter;

// std
#include <Windows.h>
#include <WinInet.h>
#include <intrin.h>
#include <iphlpapi.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <memory>
#include <vector>
#include <map>
#include <vector.h>
#include <math.h>
#include <Color.h>
#include <convar.h>
#include <icvar.h>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <array>
#include <cstdarg>
#include <Psapi.h>
#include <atlstr.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <codecvt>

// valve
#include "string_t.h"
#include "vmatrix.h"
#include "vgui\ISurface.h"
#include "vgui\IPanel.h"
#include "vgui\ISystem.h"
#include "vgui\IInput.h"
#include "vgui\IVGui.h"
#include "cdll_int.h"
#include "cdll_client_int.h"

#include "shareddefs.h"
#include "isaverestore.h"
#include "ehandle.h"
#include "groundlink.h"
#include "variant_t.h"
#include "iserverunknown.h"
#include "iservernetworkable.h"
#include "ServerNetworkProperty.h"
#include "IEngineTrace.h"
#include "takedamageinfo.h"
#include "predictableid.h"
#include "networkvar.h"
#include "touchlink.h"
#include "predictable_entity.h"
#include "baseentity_shared.h"
#include "baseentity.h"
#include "baseplayer_shared.h"
#include "c_baseentity.h"
#include "icliententity.h"
#include "icliententitylist.h"
#include "iclientmode.h"
#include "igamemovement.h"
#include "iprediction.h"
#include "IEngineTrace.h"
#include "usercmd.h"
#include "ivrenderview.h"

// non-std
#include "DEFINITIONS.h"
#include "Utils.h"
#include "CONFIG.h"

#include "CFG_ACCOUNTS.h"
#include "C_SHA256.h"
#include "Hardware.h"

// managers
#include "C_Cheat.h"
#include "C_Player.h"
#include "C_Patch.h"
#include "C_VMTHook.h"

#include "C_CheatMgr.h"
#include "C_EntityMgr.h"
#include "C_VMTHookMgr.h"
#include "C_PatchMgr.h"
#include "C_CVarMgr.h"

#include "GetVirtualFn.h"

#include "IVEngineClient.h"

#include "Hooks.h"

// cheats
#include "C_CH_LicenseChecker.h"
#include "C_CH_BunnyHop.h"
#include "C_CH_Aimbot.h"
#include "C_CH_Ceiling.h"
#include "C_CH_NoRecoil.h"
#include "C_CH_Radar.h"
#include "C_CH_AutoRespInSurv.h"
#include "C_CH_ESP.h"
#include "C_CH_FakeLag.h"
#include "C_CH_GlowHack.h"
#include "C_CH_NameStealer.h"
#include "C_CH_TeleportAndCrush.h"
#include "C_CH_MaterialHack.h"
#include "C_CH_ConfigExecuter.h"