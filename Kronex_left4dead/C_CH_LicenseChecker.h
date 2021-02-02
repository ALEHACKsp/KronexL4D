#pragma once

class C_CH_LicenseChecker : public C_Cheat
{
public:
  C_CH_LicenseChecker(C_CheatMgr* cheatManager, string cheatName);
  virtual ~C_CH_LicenseChecker();

  virtual void perform();
  virtual void restoreChanges();
  virtual void update();

  SYSTEMTIME GetServerTime(LPCSTR ServerURL);

  long long int DateToSec(int day, int month, int year, int hour, int minute, int second);

  void LicenseFailed(int ExitCode, bool needToReeboot);
  void CheckSubscriptionLicense();
  void CheckHardWareIDLicense();
  void CheckSteamIDLicense();
};

