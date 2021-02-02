#pragma once

#pragma comment(lib,"wininet")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wbemuuid.lib")

#pragma warning(disable : 4996)

#define _WIN32_DCOM

#define  IDENTIFY_BUFFER_SIZE             512

#define  DFP_GET_VERSION                  0x00074080
#define  DFP_RECEIVE_DRIVE_DATA           0x0007c088

#define  FILE_DEVICE_SCSI                 0x0000001b
#define  IOCTL_SCSI_MINIPORT_IDENTIFY     ((FILE_DEVICE_SCSI << 16) + 0x0501)
#define  IOCTL_SCSI_MINIPORT              0x0004D008  //  see NTDDSCSI.H for definition

#define SMART_GET_VERSION                 CTL_CODE(IOCTL_DISK_BASE, 0x0020, METHOD_BUFFERED, FILE_READ_ACCESS)
#define SMART_SEND_DRIVE_COMMAND          CTL_CODE(IOCTL_DISK_BASE, 0x0021, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define SMART_RCV_DRIVE_DATA              CTL_CODE(IOCTL_DISK_BASE, 0x0022, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_QUERY_PROPERTY      CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DISK_GET_DRIVE_GEOMETRY_EX  CTL_CODE(IOCTL_DISK_BASE, 0x0028, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define ID_CMD                            0xEC            // Returns ID sector for ATA
#define  m_cVxDFunctionIdesDInfo          1
#define  SENDIDLENGTH                     (sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE)

typedef struct _GETVERSIONOUTPARAMS
{
  BYTE bVersion;      // Binary driver version.
  BYTE bRevision;     // Binary driver revision.
  BYTE bReserved;     // Not used.
  BYTE bIDEDeviceMap; // Bit map of IDE devices.
  DWORD fCapabilities; // Bit mask of driver capabilities.
  DWORD dwReserved[4]; // For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

#define  CAP_IDE_ID_FUNCTION              1  // ATA ID command supported
#define  CAP_IDE_ATAPI_ID                 2  // ATAPI ID command supported
#define  CAP_IDE_EXECUTE_SMART_FUNCTION   4  // SMART commannds supported

#define  IDE_ATAPI_IDENTIFY               0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY                 0xEC  //  Returns ID sector for ATA.

typedef struct _IDSECTOR
{
  USHORT  wGenConfig;
  USHORT  wNumCyls;
  USHORT  wReserved;
  USHORT  wNumHeads;
  USHORT  wBytesPerTrack;
  USHORT  wBytesPerSector;
  USHORT  wSectorsPerTrack;
  USHORT  wVendorUnique[3];
  CHAR    sSerialNumber[20];
  USHORT  wBufferType;
  USHORT  wBufferSize;
  USHORT  wECCSize;
  CHAR    sFirmwareRev[8];
  CHAR    sModelNumber[40];
  USHORT  wMoreVendorUnique;
  USHORT  wDoubleWordIO;
  USHORT  wCapabilities;
  USHORT  wReserved1;
  USHORT  wPIOTiming;
  USHORT  wDMATiming;
  USHORT  wBS;
  USHORT  wNumCurrentCyls;
  USHORT  wNumCurrentHeads;
  USHORT  wNumCurrentSectorsPerTrack;
  ULONG   ulCurrentSectorCapacity;
  USHORT  wMultSectorStuff;
  ULONG   ulTotalAddressableSectors;
  USHORT  wSingleWordDMA;
  USHORT  wMultiWordDMA;
  BYTE    bReserved[128];
} IDSECTOR, *PIDSECTOR;


typedef struct _SRB_IO_CONTROL
{
  ULONG HeaderLength;
  UCHAR Signature[8];
  ULONG Timeout;
  ULONG ControlCode;
  ULONG ReturnCode;
  ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

typedef struct _IDENTIFY_DATA {
  USHORT GeneralConfiguration;            // 00 00
  USHORT NumberOfCylinders;               // 02  1
  USHORT Reserved1;                       // 04  2
  USHORT NumberOfHeads;                   // 06  3
  USHORT UnformattedBytesPerTrack;        // 08  4
  USHORT UnformattedBytesPerSector;       // 0A  5
  USHORT SectorsPerTrack;                 // 0C  6
  USHORT VendorUnique1[3];                // 0E  7-9
  USHORT SerialNumber[10];                // 14  10-19
  USHORT BufferType;                      // 28  20
  USHORT BufferSectorSize;                // 2A  21
  USHORT NumberOfEccBytes;                // 2C  22
  USHORT FirmwareRevision[4];             // 2E  23-26
  USHORT ModelNumber[20];                 // 36  27-46
  UCHAR  MaximumBlockTransfer;            // 5E  47
  UCHAR  VendorUnique2;                   // 5F
  USHORT DoubleWordIo;                    // 60  48
  USHORT Capabilities;                    // 62  49
  USHORT Reserved2;                       // 64  50
  UCHAR  VendorUnique3;                   // 66  51
  UCHAR  PioCycleTimingMode;              // 67
  UCHAR  VendorUnique4;                   // 68  52
  UCHAR  DmaCycleTimingMode;              // 69
  USHORT TranslationFieldsValid : 1;      // 6A  53
  USHORT Reserved3 : 15;
  USHORT NumberOfCurrentCylinders;        // 6C  54
  USHORT NumberOfCurrentHeads;            // 6E  55
  USHORT CurrentSectorsPerTrack;          // 70  56
  ULONG  CurrentSectorCapacity;           // 72  57-58
  USHORT CurrentMultiSectorSetting;       //     59
  ULONG  UserAddressableSectors;          //     60-61
  USHORT SingleWordDMASupport : 8;        //     62
  USHORT SingleWordDMAActive : 8;
  USHORT MultiWordDMASupport : 8;         //     63
  USHORT MultiWordDMAActive : 8;
  USHORT AdvancedPIOModes : 8;            //     64
  USHORT Reserved4 : 8;
  USHORT MinimumMWXferCycleTime;          //     65
  USHORT RecommendedMWXferCycleTime;      //     66
  USHORT MinimumPIOCycleTime;             //     67
  USHORT MinimumPIOCycleTimeIORDY;        //     68
  USHORT Reserved5[2];                    //     69-70
  USHORT ReleaseTimeOverlapped;           //     71
  USHORT ReleaseTimeServiceCommand;       //     72
  USHORT MajorRevision;                   //     73
  USHORT MinorRevision;                   //     74
  USHORT Reserved6[50];                   //     75-126
  USHORT SpecialFunctionsEnabled;         //     127
  USHORT Reserved7[128];                  //     128-255
} IDENTIFY_DATA, *PIDENTIFY_DATA;

typedef struct _rt_IdeDInfo_
{
  BYTE IDEExists[4];
  BYTE DiskExists[8];
  WORD DisksRawInfo[8 * 256];
} rt_IdeDInfo, *pt_IdeDInfo;

typedef struct _rt_DiskInfo_
{
  BOOL DiskExists;
  BOOL ATAdevice;
  BOOL RemovableDevice;
  WORD TotLogCyl;
  WORD TotLogHeads;
  WORD TotLogSPT;
  char SerialNumber[20];
  char FirmwareRevision[8];
  char ModelNumber[40];
  WORD CurLogCyl;
  WORD CurLogHeads;
  WORD CurLogSPT;
} rt_DiskInfo;

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
  T dest = beg;
  for (T itr = beg; itr != end; ++itr)
  {
    if (!pred(*itr))
    {
      *(dest++) = *itr;
    }
  }
  return dest;
}

char* ConvertToString(DWORD diskdata[256], int firstIndex, int lastIndex, char* buf);
string GenerateHardDriveInformation(int drive, DWORD diskdata[256], string& HardDriveInformation);
string GetInfoByWin(vector<string> vStrings);
BOOL DoIDENTIFY(HANDLE, PSENDCMDINPARAMS, PSENDCMDOUTPARAMS, BYTE, BYTE, PDWORD);

int ReadIdeDriveAsScsiDriveInNT(string& HardDriveInformation);
int ReadDrivePortsInWin9X(string& HardDriveInformation);
int ReadPhysicalDriveInNTWithZeroRights(void);
char* flipAndCodeBytes(const char * str, int pos, int flip, char * buf);
int ReadPhysicalDriveInNTUsingSmart(string& HardDriveInformation);
int ReadPhysicalDriveInNTWithAdminRights(string& HardDriveInformation);

string GetMacID();
string GetProcessorInfo();
string GetHDriveInfo();
string GetMotherBoardInfo();
string GetBIOSInfo();
string GetUSBControllerInfo();
string GetVideoControllerInfo();
string GetBusInfo();
string GetHardWareID();
