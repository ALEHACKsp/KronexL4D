#include "KronexMain.h"

static char HardDriveSerialNumber[1024];
static char HardDriveModelNumber[1024];
static BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];

string GetHardWareID()
{
  static int updateTime = 1000; // how often HWID generates in ms

  static string HardwareID = "";
  static int time_since_last_hwid_generation = 0;

  if (HardwareID.empty() || (clock() - time_since_last_hwid_generation) > updateTime)
  {
    HardwareID.clear();

    //HardwareID += MacAddress(); // unstable
    HardwareID += GetProcessorInfo();
    HardwareID += GetHDriveInfo();
    HardwareID += GetMotherBoardInfo();
    HardwareID += GetBIOSInfo();
    HardwareID += GetUSBControllerInfo();
    HardwareID += GetVideoControllerInfo();
    HardwareID += GetBusInfo();

    HardwareID.erase(std::remove_if(HardwareID.begin(), HardwareID.end(), isspace), HardwareID.end()); // remove spaces symbols
    HardwareID = sha256(HardwareID);

    time_since_last_hwid_generation = clock();
  }

  return HardwareID;
}

string GetBusInfo()
{
  vector<string> vInfo =
  {
    XS("Win32_Bus"),
    XS("DeviceID"),
  };

  return GetInfoByWin(vInfo);
}

string GetVideoControllerInfo()
{
  vector<string> vInfo =
  {
    XS("Win32_VideoController"),
    XS("AdapterCompatibility"),
    XS("AdapterDACType"),
    XS("Caption"),
    XS("Description"),
    XS("DeviceID"),
    XS("DriverVersion"),
    XS("InfSection"),
    XS("PNPDeviceID"),
    XS("VideoProcessor"),
  };

  return GetInfoByWin(vInfo);
}

string GetUSBControllerInfo()
{
  vector<string> vInfo =
  {
    XS("Win32_USBController"),
    XS("PNPDeviceID"),
  };

  return GetInfoByWin(vInfo);
}

string GetBIOSInfo()
{
  vector<string> vInfo =
  {
    XS("Win32_BIOS"),
    XS("Caption"),
    //XS("CurrentLanguage"), // crush
    XS("Description"),
    XS("Name"),
    XS("Manufacturer"),
    XS("SerialNumber"),
    XS("SMBIOSBIOSVersion"),
    XS("SoftwareElementID"),
    XS("Version"),
  };

  return GetInfoByWin(vInfo);
}

string GetMotherBoardInfo()
{
  vector<string> vInfo =
  {
    XS("Win32_BaseBoard"),
    XS("Manufacturer"),
    XS("Product"),
    XS("SerialNumber"),
    XS("Version")
  };

  return GetInfoByWin(vInfo);
}

string GetInfoByWin(vector<string> vStrings)
{
  HRESULT hres;

  hres = CoInitializeEx(0, COINIT_MULTITHREADED);
  if (FAILED(hres))
  {
    return "";
  }

  // Step 2: --------------------------------------------------
  hres = CoInitializeSecurity(
    NULL,
    -1,                          // COM authentication
    NULL,                        // Authentication services
    NULL,                        // Reserved
    RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
    RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
    NULL,                        // Authentication info
    EOAC_NONE,                   // Additional capabilities 
    NULL                         // Reserved
  );

  if (FAILED(hres))
  {
    CoUninitialize();
    //return ""; // fails
  }

  // Step 3: ---------------------------------------------------
  IWbemLocator *pLoc = NULL;

  hres = CoCreateInstance(
    CLSID_WbemLocator,
    0,
    CLSCTX_INPROC_SERVER,
    IID_IWbemLocator, (LPVOID *)&pLoc);

  if (FAILED(hres))
  {
    CoUninitialize();
    return "";
  }

  // Step 4: -----------------------------------------------------
  IWbemServices *pSvc = NULL;

  hres = pLoc->ConnectServer(
    _bstr_t(Utils::S8_WS(XS("ROOT\\CIMV2")).c_str()), // Object path of WMI namespace
    NULL,                    // User name. NULL = current user
    NULL,                    // User password. NULL = current
    0,                       // Locale. NULL indicates current
    NULL,                    // Security flags.
    0,                       // Authority (e.g. Kerberos)
    0,                       // Context object 
    &pSvc                    // pointer to IWbemServices proxy
  );

  if (FAILED(hres))
  {
    pLoc->Release();
    CoUninitialize();
    return "";
  }

  // Step 5: --------------------------------------------------
  hres = CoSetProxyBlanket(
    pSvc,                        // Indicates the proxy to set
    RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
    RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
    NULL,                        // Server principal name 
    RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
    RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
    NULL,                        // client identity
    EOAC_NONE                    // proxy capabilities 
  );

  if (FAILED(hres))
  {
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
    return "";
  }

  // Step 6: --------------------------------------------------
  IEnumWbemClassObject* pEnumerator = NULL;
  string temp = XS("SELECT * FROM ") + vStrings[0];
  hres = pSvc->ExecQuery(
    bstr_t(XS("WQL")),
    bstr_t(temp.c_str()),
    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
    NULL,
    &pEnumerator);

  if (FAILED(hres))
  {

    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
    return "";
  }

  // Step 7: -------------------------------------------------
  IWbemClassObject *pclsObj;
  ULONG uReturn = 0;

  wstring wresult = L"";

  while (pEnumerator)
  {
    HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

    if (0 == uReturn)
    {
      break;
    }

    VARIANT vtProp;

    for (int i = 1; i < (int)vStrings.size(); i++)
    {
      string str = vStrings[i];

      hr = pclsObj->Get(Utils::S8_WS(str).c_str(), 0, &vtProp, 0, 0);
      VariantClear(&vtProp);
      wresult += vtProp.bstrVal;
    }

    pclsObj->Release();
  }

  pSvc->Release();
  pLoc->Release();
  pEnumerator->Release();
  CoUninitialize();

  return Utils::WS_S8(wresult);
}

string GetProcessorInfo()
{
  string ProcessorInformation;

  char CPUString[0x20];
  char CPUBrandString[0x40];
  int CPUInfo[4] = { -1 };
  int nSteppingID = 0;
  int nModel = 0;
  int nFamily = 0;
  int nProcessorType = 0;
  int nExtendedmodel = 0;
  int nExtendedfamily = 0;
  int nBrandIndex = 0;
  int nCLFLUSHcachelinesize = 0;
  int nAPICPhysicalID = 0;
  int nFeatureInfo = 0;
  int nCacheLineSize = 0;
  int nL2Associativity = 0;
  int nCacheSizeK = 0;
  unsigned nIds, nExIds;
  bool bSSE3NewInstructions = false;
  bool bMONITOR_MWAIT = false;
  bool bCPLQualifiedDebugStore = false;
  bool bThermalMonitor2 = false;

  __cpuid(CPUInfo, 0);
  nIds = CPUInfo[0];
  memset(CPUString, 0, sizeof(CPUString));
  *((int*)CPUString) = CPUInfo[1];
  *((int*)(CPUString + 4)) = CPUInfo[3];
  *((int*)(CPUString + 8)) = CPUInfo[2];

  __cpuid(CPUInfo, 1);
  nSteppingID = CPUInfo[0] & 0xf;
  nModel = (CPUInfo[0] >> 4) & 0xf;
  nFamily = (CPUInfo[0] >> 8) & 0xf;
  nProcessorType = (CPUInfo[0] >> 12) & 0x3;
  nExtendedmodel = (CPUInfo[0] >> 16) & 0xf;
  nExtendedfamily = (CPUInfo[0] >> 20) & 0xff;
  nBrandIndex = CPUInfo[1] & 0xff;
  nCLFLUSHcachelinesize = ((CPUInfo[1] >> 8) & 0xff) * 8;
  nAPICPhysicalID = (CPUInfo[1] >> 24) & 0xff;
  bSSE3NewInstructions = (CPUInfo[2] & 0x1) || false;
  bMONITOR_MWAIT = (CPUInfo[2] & 0x8) || false;
  bCPLQualifiedDebugStore = (CPUInfo[2] & 0x10) || false;
  bThermalMonitor2 = (CPUInfo[2] & 0x100) || false;
  nFeatureInfo = CPUInfo[3];

  __cpuid(CPUInfo, 0x80000000);
  nExIds = CPUInfo[0];
  memset(CPUBrandString, 0, sizeof(CPUBrandString));

  __cpuid(CPUInfo, 0x80000002);
  memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
  __cpuid(CPUInfo, 0x80000003);
  memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
  __cpuid(CPUInfo, 0x80000004);
  memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
  __cpuid(CPUInfo, 0x80000006);
  nCacheLineSize = CPUInfo[2] & 0xff;
  nL2Associativity = (CPUInfo[2] >> 12) & 0xf;
  nCacheSizeK = (CPUInfo[2] >> 16) & 0xffff;

  ProcessorInformation += CPUString;
  if (nIds >= 1)
  {
    if (nSteppingID) ProcessorInformation += to_string(nSteppingID);
    if (nModel) ProcessorInformation += to_string(nModel);
    if (nFamily)ProcessorInformation += to_string(nFamily);
    if (nProcessorType)ProcessorInformation += to_string(nProcessorType);
    if (nExtendedmodel)ProcessorInformation += to_string(nExtendedmodel);
    if (nExtendedfamily)ProcessorInformation += to_string(nExtendedfamily);
    if (nBrandIndex)ProcessorInformation += to_string(nBrandIndex);
    if (nCLFLUSHcachelinesize)ProcessorInformation += to_string(nCLFLUSHcachelinesize);
    //if (nAPICPhysicalID)ProcessorInfortation += to_string(nAPICPhysicalID); // changes at runtime
  }

  if (nExIds >= 0x80000004) ProcessorInformation += CPUBrandString;

  if (nExIds >= 0x80000006)
  {
    ProcessorInformation += to_string(nCacheLineSize);
    ProcessorInformation += to_string(nL2Associativity);
    ProcessorInformation += to_string(nCacheSizeK);
  }

  SYSTEM_INFO info;
  GetSystemInfo(&info);

  if (info.wProcessorArchitecture)
  {
    ProcessorInformation += to_string(info.wProcessorArchitecture);
  }
  if (info.wReserved)
  {
    ProcessorInformation += to_string(info.wReserved);
  }
  if (info.dwPageSize)
  {
    ProcessorInformation += to_string(info.dwPageSize);
  }
  //if (info.lpMinimumApplicationAddress)
  //{
  //  ProcessorInformation += to_string((DWORD)info.lpMinimumApplicationAddress);
  //}
  //if (info.lpMaximumApplicationAddress)
  //{
  //  ProcessorInformation += to_string((DWORD)info.lpMaximumApplicationAddress);
  //}
  if (info.dwActiveProcessorMask)
  {
    ProcessorInformation += to_string(info.dwActiveProcessorMask);
  }
  if (info.dwNumberOfProcessors)
  {
    ProcessorInformation += to_string(info.dwNumberOfProcessors);
  }
  if (info.dwProcessorType)
  {
    ProcessorInformation += to_string(info.dwProcessorType);
  }
  if (info.dwAllocationGranularity)
  {
    ProcessorInformation += to_string(info.dwAllocationGranularity);
  }
  if (info.wProcessorLevel)
  {
    ProcessorInformation += to_string(info.wProcessorLevel);
  }
  if (info.wProcessorRevision)
  {
    ProcessorInformation += to_string(info.wProcessorRevision);
  }

  return  ProcessorInformation;
}

string GetMacID()
{
  string MacAddress;

  IP_ADAPTER_INFO *info = NULL, *pos;
  DWORD size = 0;
  GetAdaptersInfo(info, &size);
  info = (IP_ADAPTER_INFO*)malloc(size);
  GetAdaptersInfo(info, &size);

  MacAddress = "";
  for (pos = info; pos != NULL; pos = pos->Next)
  {
    MacAddress += to_string(pos->Address[0]);
    for (unsigned int i = 1; i < pos->AddressLength; i++) MacAddress += to_string(pos->Address[i]);
  }
  free(info);

  return MacAddress;
}

int ReadPhysicalDriveInNTWithAdminRights(string& HardDriveInformation)
{
  int done = FALSE;
  int drive = 0;

  for (drive = 0; drive < 16; drive++)
  {
    HANDLE hPhysicalDriveIOCTL = 0;
    char driveName[256];

    sprintf(driveName, "%s%d", XS("\\\\.\\PhysicalDrive"), drive);

    hPhysicalDriveIOCTL = CreateFile(driveName,
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
      OPEN_EXISTING, 0, NULL);

    if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
    {
      // !!!
    }
    else
    {
      GETVERSIONOUTPARAMS VersionParams;
      DWORD               cbBytesReturned = 0;

      memset((void*)&VersionParams, 0, sizeof(VersionParams));

      if (!DeviceIoControl(hPhysicalDriveIOCTL, DFP_GET_VERSION,
        NULL,
        0,
        &VersionParams,
        sizeof(VersionParams),
        &cbBytesReturned, NULL))
      {
        // !!!
      }

      if (VersionParams.bIDEDeviceMap <= 0)
      {
        // !!!
      }
      else
      {
        BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
        SENDCMDINPARAMS  scip;
        bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
          IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

        memset(&scip, 0, sizeof(scip));
        memset(IdOutCmd, 0, sizeof(IdOutCmd));

        if (DoIDENTIFY(hPhysicalDriveIOCTL,
          &scip,
          (PSENDCMDOUTPARAMS)&IdOutCmd,
          (BYTE)bIDCmd,
          (BYTE)drive,
          &cbBytesReturned))
        {
          DWORD diskdata[256];
          int ijk = 0;
          USHORT *pIdSector = (USHORT *)
            ((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;

          for (ijk = 0; ijk < 256; ijk++)
            diskdata[ijk] = pIdSector[ijk];

          GenerateHardDriveInformation(drive, diskdata, HardDriveInformation);

          done = TRUE;
        }
      }
      CloseHandle(hPhysicalDriveIOCTL);
    }
  }
  return done;
}

int ReadPhysicalDriveInNTUsingSmart(string& HardDriveInformation)
{
  int done = FALSE;
  int drive = 0;

  for (drive = 0; drive < 16; drive++)
  {
    HANDLE hPhysicalDriveIOCTL = 0;
    char driveName[256];

    sprintf(driveName, "%s%d", XS("\\\\.\\PhysicalDrive"), drive);

    hPhysicalDriveIOCTL = CreateFile(driveName,
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL, OPEN_EXISTING, 0, NULL);

    if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
    {
      // !!!
    }
    else
    {
      GETVERSIONINPARAMS GetVersionParams;
      DWORD cbBytesReturned = 0;

      memset((void*)& GetVersionParams, 0, sizeof(GetVersionParams));

      if (!DeviceIoControl(hPhysicalDriveIOCTL, SMART_GET_VERSION,
        NULL,
        0,
        &GetVersionParams, sizeof(GETVERSIONINPARAMS),
        &cbBytesReturned, NULL))
      {
        // !!!
      }
      else
      {
        ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
        PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS)malloc(CommandSize);

        Command->irDriveRegs.bCommandReg = ID_CMD;
        DWORD BytesReturned = 0;
        if (!DeviceIoControl(hPhysicalDriveIOCTL,
          SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),
          Command, CommandSize,
          &BytesReturned, NULL))
        {

        }
        else
        {
          DWORD diskdata[256];
          USHORT *pIdSector = (USHORT *)
            (PIDENTIFY_DATA)((PSENDCMDOUTPARAMS)Command)->bBuffer;

          for (int ijk = 0; ijk < 256; ijk++)
            diskdata[ijk] = pIdSector[ijk];

          GenerateHardDriveInformation(drive, diskdata, HardDriveInformation);
          done = TRUE;
        }
        CloseHandle(hPhysicalDriveIOCTL);
        free(Command);
      }
    }
  }
  return done;
}

char* flipAndCodeBytes(const char * str, int pos, int flip, char * buf)
{
  int i;
  int j = 0;
  int k = 0;

  buf[0] = '\0';
  if (pos <= 0)
    return buf;

  if (!j)
  {
    char p = 0;

    j = 1;
    k = 0;
    buf[k] = 0;
    for (i = pos; j && str[i] != '\0'; ++i)
    {
      char c = tolower(str[i]);

      if (isspace(c))
        c = '0';

      ++p;
      buf[k] <<= 4;

      if (c >= '0' && c <= '9')
        buf[k] |= (unsigned char)(c - '0');
      else if (c >= 'a' && c <= 'f')
        buf[k] |= (unsigned char)(c - 'a' + 10);
      else
      {
        j = 0;
        break;
      }

      if (p == 2)
      {
        if (buf[k] != '\0' && !isprint(buf[k]))
        {
          j = 0;
          break;
        }
        ++k;
        p = 0;
        buf[k] = 0;
      }

    }
  }

  if (!j)
  {
    j = 1;
    k = 0;
    for (i = pos; j && str[i] != '\0'; ++i)
    {
      char c = str[i];

      if (!isprint(c))
      {
        j = 0;
        break;
      }

      buf[k++] = c;
    }
  }

  if (!j)
  {
    k = 0;
  }

  buf[k] = '\0';

  if (flip)
    for (j = 0; j < k; j += 2)
    {
      char t = buf[j];
      buf[j] = buf[j + 1];
      buf[j + 1] = t;
    }

  i = j = -1;
  for (k = 0; buf[k] != '\0'; ++k)
  {
    if (!isspace(buf[k]))
    {
      if (i < 0)
        i = k;
      j = k;
    }
  }

  if ((i >= 0) && (j >= 0))
  {
    for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
      buf[k - i] = buf[k];
    buf[k - i] = '\0';
  }

  return buf;
}

int ReadPhysicalDriveInNTWithZeroRights(void)
{
  int done = FALSE;
  int drive = 0;

  for (drive = 0; drive < 16; drive++)
  {
    HANDLE hPhysicalDriveIOCTL = 0;
    char driveName[256];

    sprintf(driveName, "%s%d", XS("\\\\.\\PhysicalDrive"), drive);

    hPhysicalDriveIOCTL = CreateFile(driveName, 0,
      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
      OPEN_EXISTING, 0, NULL);
    if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
    {
      // !!!
    }
    else
    {
      STORAGE_PROPERTY_QUERY query;
      DWORD cbBytesReturned = 0;
      char local_buffer[10000];

      memset((void *)& query, 0, sizeof(query));
      query.PropertyId = StorageDeviceProperty;
      query.QueryType = PropertyStandardQuery;

      memset(local_buffer, 0, sizeof(local_buffer));

      if (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,
        &query,
        sizeof(query),
        &local_buffer[0],
        sizeof(local_buffer),
        &cbBytesReturned, NULL))
      {
        STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *)& local_buffer;
        char serialNumber[1000];
        char modelNumber[1000];
        char vendorId[1000];
        char productRevision[1000];

        flipAndCodeBytes(local_buffer, descrip->VendorIdOffset, 0, vendorId);
        flipAndCodeBytes(local_buffer, descrip->ProductIdOffset, 0, modelNumber);
        flipAndCodeBytes(local_buffer, descrip->ProductRevisionOffset, 0, productRevision);
        flipAndCodeBytes(local_buffer, descrip->SerialNumberOffset, 1, serialNumber);

        if (0 == HardDriveSerialNumber[0] && (isalnum(serialNumber[0]) || isalnum(serialNumber[19])))
        {
          strcpy(HardDriveSerialNumber, serialNumber);
          strcpy(HardDriveModelNumber, modelNumber);
          done = TRUE;
        }
      }
      else
      {
        // !!!
      }

      CloseHandle(hPhysicalDriveIOCTL);
    }
  }

  return done;
}

BOOL DoIDENTIFY(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP, PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum, PDWORD lpcbBytesReturned)
{
  pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
  pSCIP->irDriveRegs.bFeaturesReg = 0;
  pSCIP->irDriveRegs.bSectorCountReg = 1;
  pSCIP->irDriveRegs.bCylLowReg = 0;
  pSCIP->irDriveRegs.bCylHighReg = 0;

  pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

  pSCIP->irDriveRegs.bCommandReg = bIDCmd;
  pSCIP->bDriveNumber = bDriveNum;
  pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

  return (DeviceIoControl(hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
    (LPVOID)pSCIP,
    sizeof(SENDCMDINPARAMS) - 1,
    (LPVOID)pSCOP,
    sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
    lpcbBytesReturned, NULL));
}

int ReadDrivePortsInWin9X(string& HardDriveInformation)
{
  int done = FALSE;
  unsigned long int i = 0;

  HANDLE VxDHandle = 0;
  pt_IdeDInfo pOutBufVxD = 0;
  DWORD lpBytesReturned = 0;

  SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

  rt_IdeDInfo info;
  pOutBufVxD = &info;

  ZeroMemory(&info, sizeof(info));

  VxDHandle = CreateFile(XS("\\\\.\\IDE21201.VXD"), 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);

  if (VxDHandle != INVALID_HANDLE_VALUE)
  {
    DeviceIoControl(VxDHandle, m_cVxDFunctionIdesDInfo, 0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);
    CloseHandle(VxDHandle);
  }

  for (i = 0; i<8; i++)
  {
    if ((pOutBufVxD->DiskExists[i]) && (pOutBufVxD->IDEExists[i / 2]))
    {
      DWORD diskinfo[256];
      for (int j = 0; j < 256; j++)
        diskinfo[j] = pOutBufVxD->DisksRawInfo[i * 256 + j];

      GenerateHardDriveInformation(i, diskinfo, HardDriveInformation);
      done = TRUE;
    }
  }

  SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
  return done;
}

int ReadIdeDriveAsScsiDriveInNT(string& HardDriveInformation)
{
  int done = FALSE;
  int controller = 0;

  for (controller = 0; controller < 16; controller++)
  {
    HANDLE hScsiDriveIOCTL = 0;
    char   driveName[256];

    sprintf(driveName, "%s%d:", XS("\\\\.\\Scsi"), controller);

    hScsiDriveIOCTL = CreateFile(driveName,
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
      OPEN_EXISTING, 0, NULL);

    if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
    {
      int drive = 0;

      for (drive = 0; drive < 2; drive++)
      {
        char buffer[sizeof(SRB_IO_CONTROL) + SENDIDLENGTH];
        SRB_IO_CONTROL *p = (SRB_IO_CONTROL *)buffer;
        SENDCMDINPARAMS *pin =
          (SENDCMDINPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
        DWORD dummy;

        memset(buffer, 0, sizeof(buffer));
        p->HeaderLength = sizeof(SRB_IO_CONTROL);
        p->Timeout = 10000;
        p->Length = SENDIDLENGTH;
        p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
        strncpy((char *)p->Signature, XS("SCSIDISK"), 8);

        pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
        pin->bDriveNumber = drive;

        if (DeviceIoControl(hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT,
          buffer,
          sizeof(SRB_IO_CONTROL) +
          sizeof(SENDCMDINPARAMS) - 1,
          buffer,
          sizeof(SRB_IO_CONTROL) + SENDIDLENGTH,
          &dummy, NULL))
        {
          SENDCMDOUTPARAMS *pOut =
            (SENDCMDOUTPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
          IDSECTOR *pId = (IDSECTOR *)(pOut->bBuffer);
          if (pId->sModelNumber[0])
          {
            DWORD diskdata[256];
            int ijk = 0;
            USHORT *pIdSector = (USHORT *)pId;

            for (ijk = 0; ijk < 256; ijk++)
              diskdata[ijk] = pIdSector[ijk];

            GenerateHardDriveInformation(controller * 2 + drive, diskdata, HardDriveInformation);

            done = TRUE;
          }
        }
      }
      CloseHandle(hScsiDriveIOCTL);
    }
  }
  return done;
}

string GenerateHardDriveInformation(int drive, DWORD diskdata[256], string& HardDriveInformation)
{
  char serialNumber[1024];
  char modelNumber[1024];
  char revisionNumber[1024];
  char bufferSize[32];

  __int64 sectors = 0;
  __int64 bytes = 0;

  ConvertToString(diskdata, 10, 19, serialNumber);
  ConvertToString(diskdata, 27, 46, modelNumber);
  ConvertToString(diskdata, 23, 26, revisionNumber);
  sprintf(bufferSize, "%u", diskdata[21] * 512);

  if (0 == HardDriveSerialNumber[0] && (isalnum(serialNumber[0]) || isalnum(serialNumber[19])))
  {
    strcpy(HardDriveSerialNumber, serialNumber);
    strcpy(HardDriveModelNumber, modelNumber);
  }

  HardDriveInformation = "";
  HardDriveInformation += modelNumber;
  HardDriveInformation += serialNumber;
  HardDriveInformation += revisionNumber;
  HardDriveInformation += bufferSize;
  if (diskdata[0] & 0x0080) HardDriveInformation += XS("Removable");
  else if (diskdata[0] & 0x0040) HardDriveInformation += XS("Fixed");
  else HardDriveInformation += XS("Unknown");

  if (diskdata[83] & 0x400)
    sectors = diskdata[103] * 65536I64 * 65536I64 * 65536I64 +
    diskdata[102] * 65536I64 * 65536I64 +
    diskdata[101] * 65536I64 +
    diskdata[100];
  else
    sectors = diskdata[61] * 65536 + diskdata[60];

  bytes = sectors * 512;
  HardDriveInformation += to_string(bytes);

  return HardDriveInformation;
}

char* ConvertToString(DWORD diskdata[256], int firstIndex, int lastIndex, char* buf)
{
  int index = 0;
  int position = 0;

  for (index = firstIndex; index <= lastIndex; index++)
  {
    buf[position++] = (char)(diskdata[index] / 256);

    buf[position++] = (char)(diskdata[index] % 256);
  }

  buf[position] = '\0';

  for (index = position - 1; index > 0 && isspace(buf[index]); index--) buf[index] = '\0';

  return buf;
}

string GetHDriveInfo()
{
  string HardDriveInformation;
  int done = FALSE;
  __int64 id = 0;
  OSVERSIONINFO version;

  strcpy(HardDriveSerialNumber, "");

  memset(&version, 0, sizeof(version));
  version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&version);
  if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
  {
    done = ReadPhysicalDriveInNTWithAdminRights(HardDriveInformation);

    if (!done)
    {
      done = ReadIdeDriveAsScsiDriveInNT(HardDriveInformation);
    }

    if (!done)
    {
      done = ReadPhysicalDriveInNTWithZeroRights();
    }

    if (!done)
    {
      done = ReadPhysicalDriveInNTUsingSmart(HardDriveInformation);
    }
  }
  else
  {
    int attempt = 0;

    for (attempt = 0; attempt < 10 && !done && 0 == HardDriveSerialNumber[0]; attempt++)
    {
      done = ReadDrivePortsInWin9X(HardDriveInformation);
    }
  }

  if (HardDriveSerialNumber[0] > 0)
  {
    char *p = HardDriveSerialNumber;

    if (!strncmp(HardDriveSerialNumber, XS("WD-W"), 4)) p += 5;
    for (; p && *p; p++)
    {
      if ('-' == *p)
        continue;
      id *= 10;
      switch (*p)
      {
        case '0': id += 0; break;
        case '1': id += 1; break;
        case '2': id += 2; break;
        case '3': id += 3; break;
        case '4': id += 4; break;
        case '5': id += 5; break;
        case '6': id += 6; break;
        case '7': id += 7; break;
        case '8': id += 8; break;
        case '9': id += 9; break;
        case 'a': case 'A': id += 10; break;
        case 'b': case 'B': id += 11; break;
        case 'c': case 'C': id += 12; break;
        case 'd': case 'D': id += 13; break;
        case 'e': case 'E': id += 14; break;
        case 'f': case 'F': id += 15; break;
        case 'g': case 'G': id += 16; break;
        case 'h': case 'H': id += 17; break;
        case 'i': case 'I': id += 18; break;
        case 'j': case 'J': id += 19; break;
        case 'k': case 'K': id += 20; break;
        case 'l': case 'L': id += 21; break;
        case 'm': case 'M': id += 22; break;
        case 'n': case 'N': id += 23; break;
        case 'o': case 'O': id += 24; break;
        case 'p': case 'P': id += 25; break;
        case 'q': case 'Q': id += 26; break;
        case 'r': case 'R': id += 27; break;
        case 's': case 'S': id += 28; break;
        case 't': case 'T': id += 29; break;
        case 'u': case 'U': id += 30; break;
        case 'v': case 'V': id += 31; break;
        case 'w': case 'W': id += 32; break;
        case 'x': case 'X': id += 33; break;
        case 'y': case 'Y': id += 34; break;
        case 'z': case 'Z': id += 35; break;
      }
    }
  }

  id %= 100000000;
  if (strstr(HardDriveModelNumber, XS("IBM-"))) id += 300000000;
  else if (strstr(HardDriveModelNumber, XS("MAXTOR")) || strstr(HardDriveModelNumber, XS("Maxtor"))) id += 400000000;
  else if (strstr(HardDriveModelNumber, XS("WDC "))) id += 500000000;
  else id += 600000000;

  HardDriveInformation += to_string(id);

  return HardDriveInformation;
}
