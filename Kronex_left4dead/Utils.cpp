#include "KronexMain.h"

ValueTypes Utils::GetValueType(const string &str)
{
  if (str.empty())
    return UnknownValue;

  if (IsFloat(str) || IsInt(str))
  {
    if (size_t found = str.find(XS(".")))
    {
      if (found != string::npos)
      {
        return FloatValue;
      }
      else return IntValue;
    }
    if (size_t found = str.find(XS("f")))
    {
      if (found != string::npos)
      {
        return FloatValue;
      }
      else return IntValue;
    }
  }
  return StringValue;
}

bool Utils::IsFloat(const string &str)
{
  try
  {
    stof(str);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool Utils::IsInt(const string &str)
{
  try
  {
    stoi(str);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

vector<int> Utils::SeparatorPos(const string &str, const string &separator)
{
  // "cvar ?:_123 ?:_456 ?:_789", " ?:_" // 4 11 18
  vector<int> vResult;

  for (int i = 0; i < (int)str.length(); i++)
  {
    bool bSuccess = true;
    for (int j = 0; j < (int)separator.length(); j++)
    {
      if (i + j < (int)str.length())
      {
        if (str[i + j] != separator[j])
        {
          bSuccess = false;
          break;
        }
      }
      else
      {
        bSuccess = false;
        break;
      }
      if (j + 1 == (int)separator.length())
      {
        if (bSuccess)
        {
          vResult.push_back(i);
          i += (int)separator.length() - 1;
        }
      }
    }
  }
  return vResult;
}

vector<string> Utils::split_S8(const string &str, const string &separator)
{
  // "cvar ?:_123 ?:_456 ?:_789", " ?:_" // cvar 123 456 789
  vector<string> vResult;
  vector<int> vPositions = SeparatorPos(str, separator);

  if (vPositions.empty()) return vResult;

  string sTemp;

  for (int i = 0, vPosElement = 0; i < (int)str.length(); i++)
  {
    if (i == vPositions[vPosElement])
    {
      vResult.push_back(sTemp);
      sTemp.clear();

      if (vPosElement < (int)vPositions.size())
      {
        i = vPositions[vPosElement] + separator.length() - 1;
        vPosElement++;
      }

    }
    else
    {
      sTemp += str[i];
    }
  }
  vResult.push_back(sTemp);

  return vResult;
}

vector<string> Utils::split_S8(const string &str, const char separator)
{
  return split_S8(str, "" + separator);
}

void Utils::DrawFilledCircle(int x, int y, int radius, int segments)
{
  for (int i = 0; i < radius; i++)
  {
    g_pSurface->DrawOutlinedCircle(x, y, radius - i, segments);
    //g_pSurface->DrawOutlinedCircle(x + 1, y, radius - i, segments);
    //g_pSurface->DrawOutlinedCircle(x - 1, y, radius - i, segments);
    //g_pSurface->DrawOutlinedCircle(x, y + 1, radius - i, segments);
    //g_pSurface->DrawOutlinedCircle(x, y - 1, radius - i, segments);
  }
}

void Utils::DrawOutlinedRect(int x0, int y0, int x1, int y1, int thickness)
{
  thickness = 1;
  if (thickness < 1) thickness = 1;

  for (int i = 0; i < thickness; i++)
  {
    g_pSurface->DrawOutlinedRect(x0 + i, y0 + i, x1 - i, y1 - i);
  }
}

void Utils::DrawLine(int x0, int y0, int x1, int y1, int thickness)
{
  thickness = 1;
  if (thickness < 1) thickness = 1;

  for (int i = 0; i < thickness; i++)
  {
    g_pSurface->DrawLine(x0 + i, y0, x1 + i, y1);
  }
}

void Utils::DrawPrintText(const string &text, vgui::FontDrawType_t drawType)
{
  wstring text_w = S8_WS(text);
  g_pSurface->DrawPrintText(text_w.c_str(), text_w.length(), drawType);
}

string Utils::U16S_S8(const u16string &u16str)
{
  wstring_convert<codecvt_utf8_utf16<int16_t>, int16_t> converter;
  auto p = reinterpret_cast<const int16_t *>(u16str.data());
  return converter.to_bytes(p, p + u16str.size());
}

u16string Utils::S8_U16S(const string &str8)
{
  wstring_convert<codecvt_utf8_utf16<int16_t>, int16_t> converter;
  return *(u16string*)(&(converter.from_bytes(str8)));
}

wstring Utils::S8_WS(const string &str8)
{
  return wstring(str8.begin(), str8.end());
}

string Utils::WS_S8(const wstring &wstr)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;
  return converterX.to_bytes(wstr);
}

void* Utils::FindPattern(DWORD module, string pattern, string callInfo, int dwFinalOffset)
{
  // example: AA F5 00 C2 ?? 7E 81
  if (pattern.length() < 2) return NULL;

  MODULEINFO mInfo;
  switch (module)
  {
    case Modules::Client: mInfo = C_CheatMgr::Instance->miClientDll; break;
    case Modules::Engine: mInfo = C_CheatMgr::Instance->miEngineDll; break;
    case Modules::Server: mInfo = C_CheatMgr::Instance->miServerDll; break;
    case Modules::VStdLib: mInfo = C_CheatMgr::Instance->miVstdlibDll; break;
    case Modules::MaterialSystem: mInfo = C_CheatMgr::Instance->miMaterialSystemDll; break;
    case Modules::VGUIMatSurface: mInfo = C_CheatMgr::Instance->miVGuiMatSurfaceDll; break;
    case Modules::VGUI2: mInfo = C_CheatMgr::Instance->miVGui2Dll; break;
    case Modules::OverlayRenderer: mInfo = C_CheatMgr::Instance->miOverlayRendererDll; break;
    default: GetModuleInformation(C_CheatMgr::Instance->hCurProcess, (HMODULE)C_CheatMgr::Instance->hCurProcess, &mInfo, sizeof(MODULEINFO)); break;
  }

  string bytes;
  string mask;

  Utils::PatternToHexString(pattern, bytes, mask);

  DWORD bytesCount = pattern.length() == 2 ? 1 : count(pattern.begin(), pattern.end(), ' ') + 1;
  if (bytesCount < 1) return false;

  for (DWORD i = 0; i < mInfo.SizeOfImage - bytesCount + 1; i++)
  {
    for (DWORD j = 0; j < bytesCount; j++)
    {
      if (mask[j] == 'x' && bytes[j] != *(char*)((DWORD)mInfo.lpBaseOfDll + i + j))
      {
        break;
      }
      if (j + 1 == bytesCount)
      {
        return (void*)((DWORD)mInfo.lpBaseOfDll + i + dwFinalOffset);
      }
    }
  }

  if (C_CheatMgr::Instance->user.bDebugInformation) cout << XS("Pattern not found! [") << callInfo << XS("]") << endl;
  return NULL;
}

const float Utils::Get2dDistance(float* point1, float* point2)
{
	return (float)sqrt(pow(double(point2[0] - point1[0]), 2.0f) +
						         pow(double(point2[1] - point1[1]), 2.0f));
}

const float Utils::Get3dDistance(float* point1, float* point2)
{
	return (float)sqrt(pow(double(point2[0] - point1[0]), 2.0f) +
						         pow(double(point2[1] - point1[1]), 2.0f) +
						         pow(double(point2[2] - point1[2]), 2.0f));
}


const float Utils::GetAngleDistance(float* angle1, float* angle2)
{
  float angleToTarget = Utils::Get3dDistance(angle1, angle2);
  if (angleToTarget >= 180.0f) angleToTarget = 360.0f - angleToTarget;
  
  return angleToTarget;
}


const float Utils::Get2dSummaryVelocity(float velocity1, float velocity2)
{
  return (float)sqrt(pow(velocity1, 2.0f) + pow(velocity2, 2.0f));
}

const float Utils::Get3dSummaryVelocity(float velocity1, float velocity2, float velocity3)
{
  return (float)sqrt(pow(velocity1, 2.0f) + pow(velocity2, 2.0f) + pow(velocity3, 2.0f));
}

const void Utils::LimitVector(Vector &vector)
{
  if (vector.x > 180)
    vector.x -= 360;
  if (vector.x < -180)
    vector.x += 360;

  if (vector.y > 180)
    vector.y -= 360;
  if (vector.y < -180)
    vector.y += 360;
}

const void Utils::LimitAngles(QAngle &angles)
{
  if (angles.x > 180)
    angles.x -= 360;
  if (angles.x < -180)
    angles.x += 360;

  if (angles.y > 180)
    angles.y -= 360;
  if (angles.y < -180)
    angles.y += 360;
}

const DWORD Utils::PatternToHexString(const string &pattern, string &hexString)
{
  DWORD bytesCount = CountPatternBytes(pattern);
  if (bytesCount < 1) return NULL;

  hexString = "";

  string tempHexByte;
  for (DWORD i = 0, j = 0; i < bytesCount; i++, j += 3)
  {
    tempHexByte = pattern.substr(j, 2);

    if (tempHexByte.compare(XS("??")) == 0)
    {
      hexString += 0x2A;
    }
    else
    {
      hexString += strtoul(tempHexByte.c_str(), 0, 16);
    }
  }

  return bytesCount;
}

const DWORD Utils::PatternToHexString(const string &pattern, string &hexString, string &mask)
{
  DWORD bytesCount = CountPatternBytes(pattern);
  if (bytesCount < 1) return NULL;

  hexString = "";
  mask = "";

  string tempHexByte;
  for (DWORD i = 0, j = 0; i < bytesCount; i++, j += 3)
  {
    tempHexByte = pattern.substr(j, 2);

    if (tempHexByte.compare(XS("??")) == 0)
    {
      hexString += 0x2A;
      mask += '?';
    }
    else
    {
      hexString += strtoul(tempHexByte.c_str(), 0, 16);
      mask += 'x';
    }
  }

  return bytesCount;
}

const bool Utils::MemCopyToPattern(string& pattern, void* src, DWORD size)
{
  if (size < 1) return false;

  for (DWORD i = 0; i < size; i++)
  {
    pattern += ByteToHex(*(byte*)((DWORD)src + i));
    if (i + 1 < size) pattern += XS(" ");
  }

  return true;
}

const DWORD Utils::CountPatternBytes(const string &pattern)
{
  if (pattern.length() < 2) return NULL;

  return pattern.length() == 2 ? 1 : count(pattern.begin(), pattern.end(), ' ') + 1;
}

const string Utils::ByteToHex(byte b)
{
  if (b > (byte)255) return XS("00");

  char temp[3];
  sprintf(temp, "%02X\0", b);
  return string(temp);
}

const void Utils::HexStringToPattern(const string &hexString, string &pattern, DWORD length)
{
  for (DWORD i = 0; i < length; i++)
  {
    pattern += ByteToHex(hexString[i]);
    if(i + 1 < length) pattern += " ";
  }
}

const wchar_t* Utils::GetWC(const char *c)
{
  const size_t cSize = strlen(c) + 1;

  wstring wc(cSize, L'#');
  mbstowcs(&wc[0], c, cSize);

  return wc.data();
}