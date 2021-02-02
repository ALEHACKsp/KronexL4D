#include "KronexMain.h"

int IVEngineClientMy::GetLocalPlayer()
{
  typedef int(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 12)(this);
}

bool IVEngineClientMy::IsInGame()
{
  typedef bool(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 26)(this);
}

bool IVEngineClientMy::IsConnected()
{
  typedef bool(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 27)(this);
}

bool IVEngineClientMy::IsTakingScreenshot()
{
  typedef bool(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 87)(this);
}

void IVEngineClientMy::GetScreenSize(int& width, int& height)
{
  typedef void(__thiscall* OriginalFn)(void*, int&, int&);
  return GetVFunc<OriginalFn>(this, 5)(this, width, height);
}

bool IVEngineClientMy::GetPlayerInfo(int ent, pinfo_s* pinfo)
{
  typedef bool(__thiscall* OriginalFn)(void*, int, pinfo_s*);
  return GetVFunc<OriginalFn>(this, 8)(this, ent, pinfo);
}

int	IVEngineClientMy::GetPlayerForUserID(int userID)
{
  typedef int(__thiscall* OriginalFn)(void*, int userID);
  return GetVFunc<OriginalFn>(this, 9)(this, userID);
}

bool IVEngineClientMy::Con_IsVisible()
{
  typedef bool(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 11)(this);
}

float IVEngineClientMy::Time()
{
  typedef float(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 14)(this);
}

void IVEngineClientMy::GetViewAngles(Vector& vAngle)
{
  typedef void(__thiscall* OriginalFn)(void*, Vector& vAngle);
  return GetVFunc<OriginalFn>(this, 19)(this, vAngle);
}

void IVEngineClientMy::SetViewAngles(Vector& vAngle)
{
  typedef void(__thiscall* OriginalFn)(void*, Vector& vAngle);
  return GetVFunc<OriginalFn>(this, 20)(this, vAngle);
}

int IVEngineClientMy::GetMaxClients()
{
  typedef int(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 21)(this);
}

bool IVEngineClientMy::IsDrawingLoadingImage()
{
  typedef bool(__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 28)(this);
}

const matrix3x4& IVEngineClientMy::WorldToScreenMatrix()
{
  typedef const matrix3x4& (__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 37)(this);
}

DWORD* IVEngineClientMy::GetNetChannelInfo()
{
  typedef DWORD* (__thiscall* OriginalFn)(void*);
  return GetVFunc<OriginalFn>(this, 72)(this);
}

void IVEngineClientMy::ExecCMD(const char* chCommandString)
{
  typedef void(__thiscall* OriginalFn)(void*, const char*);
  return GetVFunc<OriginalFn>(this, 105)(this, chCommandString);
}