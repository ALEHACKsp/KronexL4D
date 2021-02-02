#pragma once

typedef struct
{
  int64_t __pad0;
  union {
    int64_t xuid;
    struct {
      int xuidlow;
      int xuidhigh;
    };
  };
  char name[128];
  int userid;
  char guid[33];
  unsigned int friendsid;
  char friendsname[128];
  bool fakeplayer;
  bool ishltv;
  unsigned int customfiles[4];
  unsigned char filesdownloaded;
} pinfo_s;

class IVEngineClientMy
{
public:
  int GetLocalPlayer();
  bool IsInGame();
  bool IsConnected();
  bool IsTakingScreenshot();
  void GetScreenSize(int& width, int& height);
  bool GetPlayerInfo(int ent, pinfo_s* pinfo);
  bool Con_IsVisible();
  float Time();
  void GetViewAngles(Vector& vAngle);
  void SetViewAngles(Vector& vAngle);
  int GetMaxClients();
  bool IsDrawingLoadingImage();
  const matrix3x4& WorldToScreenMatrix();
  DWORD* GetNetChannelInfo();
  void ExecCMD(const char* chCommandString);
  int	GetPlayerForUserID(int userID);
  // int GetCommandNumber() // TODO
};

extern IVEngineClientMy* g_pEngineClient;