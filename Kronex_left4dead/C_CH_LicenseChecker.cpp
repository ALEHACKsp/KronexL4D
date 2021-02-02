#include "KronexMain.h"

C_CH_LicenseChecker::C_CH_LicenseChecker(C_CheatMgr* cheatManager, string cheatName)
  : C_Cheat(cheatManager, cheatName)
{
  if (pCMgr->user.bDebugInformation) cout << XS("Hello, ") << pCMgr->user.sName << endl;

  m_iPerformSleepTime = 100;
  m_iUpdateSleepTime = 1000;
  m_bIsCheatEnabled = true;
  m_bIsCheatInitialized = true;
}

C_CH_LicenseChecker::~C_CH_LicenseChecker()
{

}

void C_CH_LicenseChecker::update()
{

}

void C_CH_LicenseChecker::perform()
{
  if (m_bIsCheatEnabled)
  {
    CheckHardWareIDLicense();
    CheckSteamIDLicense();
    CheckSubscriptionLicense();
  }
}

void C_CH_LicenseChecker::restoreChanges()
{

}

void C_CH_LicenseChecker::CheckHardWareIDLicense()
{
  if (pCMgr->user.bHWIDCheck == true)
  {    
    if (pCMgr->user.sHWID.empty() && pCMgr->user.sRootHWID.empty())
    {
      LicenseFailed(0, true);
    }
    else
    {
      string CurrentHardWare = GetHardWareID();

      if (pCMgr->user.sHWID.compare(CurrentHardWare) != 0
          && pCMgr->user.sRootHWID.compare(CurrentHardWare) != 0)
      {
        LicenseFailed(0, true);
      }
    }
  }
}

void C_CH_LicenseChecker::CheckSteamIDLicense()
{
  if (pCMgr->user.bSTEAMIDCheck)
  {
    if (!pCMgr->user.sSTEAMID.empty())
    {
      if (pCMgr->user.sSTEAMID.compare(to_string(*pCMgr->m_plliSteamID)) == 0) return;
      else
      {
        LicenseFailed(0, true);
      }
    }
    else
    {
      LicenseFailed(0, true);
    }
  }
}

void C_CH_LicenseChecker::CheckSubscriptionLicense()
{
  LPCSTR SNTP_SERVERS_URL[] =
  {
    XS("http://vk.com"),
    XS("http://yandex.ru"),
    XS("http://google.com"),
    XS("http://amazon.com"),
    XS("http://ebay.com"),
    XS("http://facebook.com"),
    XS("http://twitter.com"),
    XS("http://linkedin.com"),
    XS("http://youtube.com"),
    XS("http://wikipedia.com"),
  };

  if (pCMgr->user.bCheckExpireTime)
  {
    SYSTEMTIME serverTime;

    int sDay;
    int sMonth;
    int sYear;
    int sHour;
    int sMinute;
    int sSecond;

    int NumOfServers = sizeof(SNTP_SERVERS_URL) / sizeof(LPCSTR);

    for (int i = 0; i < NumOfServers; i++)
    {
      serverTime = GetServerTime(SNTP_SERVERS_URL[i]);

      sDay = serverTime.wDay;
      sMonth = serverTime.wMonth;
      sYear = serverTime.wYear;
      sHour = serverTime.wHour;
      sMinute = serverTime.wMinute;
      sSecond = serverTime.wSecond;

      int iDay = pCMgr->user.iDate[0];
      int iMonth = pCMgr->user.iDate[1];
      int iYear = pCMgr->user.iDate[2];
      int iHour = pCMgr->user.iTime[0];
      int iMinute = pCMgr->user.iTime[1];
      int iSecond = pCMgr->user.iTime[2];

      //cout << "sDay:" << sDay << endl;
      //cout << "sMonth:" << sMonth << endl;
      //cout << "sYear:" << sYear << endl;
      //cout << "sHour:" << sHour << endl;
      //cout << "sMinute:" << sMinute << endl;
      //cout << "sSecond:" << sSecond << endl;

      //cout << "iDay:" << iDay << endl;
      //cout << "iMonth:" << iMonth << endl;
      //cout << "iYear:" << iYear << endl;
      //cout << "iHour:" << iHour << endl;
      //cout << "iMinute:" << iMinute << endl;
      //cout << "iSecond:" << iSecond << endl;

      //Sleep(10000);

      //if (iHour >= 3)
      //{
      //  iHour -= 3;
      //}
      //else
      //{
      //  if (iDay > 0)
      //  {
      //    iHour += 21;
      //    iDay--;
      //  }
      //}

      if (DateToSec(iDay, iMonth, iYear, iHour, iMinute, iSecond) > DateToSec(sDay, sMonth, sYear, sHour, sMinute, sSecond)) return;
      else
      {
        if (i + 1 == NumOfServers)
        {
          LicenseFailed(0, true);
        }
      }

      //this_thread::sleep_for(chrono::milliseconds(1000));
    }
  }
}

void C_CH_LicenseChecker::LicenseFailed(int ExitCode, bool needToReeboot)
{
  //Beep(1200, 200);
  //Beep(1200, 200);
  //Beep(1200, 200);

  //*(int*)(0x53) = 0;

  C_CVarMgr::FindVar(XS("krx_kronex_enabled"))->SetValue(0);

  //ShellExecute(0, 0, XS("https://vk.com/im?sel=45357784"), 0, 0, SW_SHOW);

  //ShellExecuteA(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd);
  //if ((HMODULE)C_CheatMgr::Instance)
  //{
  //  delete (HMODULE)C_CheatMgr::Instance;
  //}

  //FreeConsole();
  //fclose(stdout);
  //fclose(stdin);


  ////if (needToReeboot)
  ////{
  ////  WinExec(XorStr("shutdown -s -t 1 -f"), SW_HIDE); // выключение
  ////  //WinExec(XorStr("shutdown -r -t 1 -f"), SW_HIDE); // перезагрузка
  ////  //WinExec(XorStr("shutdown -l -t 0"), SW_HIDE); // выход
  ////}

  //FreeLibraryAndExitThread((HMODULE)C_CheatMgr::Instance->m_hInstanceDll, ExitCode);
  //exit(ExitCode);
}

SYSTEMTIME C_CH_LicenseChecker::GetServerTime(LPCSTR ServerURL)
{
  SYSTEMTIME sysTime;
  SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));

  HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);

  if (!hInternetSession) return sysTime;

  HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, ServerURL, NULL, NULL, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);

  if (!hInternetFile)
  {
    InternetCloseHandle(hInternetSession);
    return sysTime;
  }

  DWORD dwSize = sizeof(SYSTEMTIME);
  if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
  {
    InternetCloseHandle(hInternetSession);
    InternetCloseHandle(hInternetFile);
    return sysTime;
  }

  InternetCloseHandle(hInternetFile);
  InternetCloseHandle(hInternetSession);
  return sysTime;
}

long long int C_CH_LicenseChecker::DateToSec(int day, int month, int year, int hour, int minute, int second)
{
  long long int tmp_Time = 0;

  tmp_Time += second;
  tmp_Time += minute * 60;
  tmp_Time += hour * 60 * 60;
  tmp_Time += day * 24 * 60 * 60;
  tmp_Time += month * 31 * 24 * 60 * 60;
  tmp_Time += (year - 2015) * 365 * 24 * 60 * 60;

  return tmp_Time;
}