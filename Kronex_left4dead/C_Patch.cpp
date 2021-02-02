#include "KronexMain.h"

C_Patch::C_Patch(const string &name, void* dst, const string &newBytes)
  : m_sName(name), 
    m_pDestination(dst),
    m_sNewBytes(newBytes),
    m_bPatched(false)
{
  m_dwCountNewBytes = Utils::CountPatternBytes(m_sNewBytes);
  m_dwCountOldBytes = m_dwCountNewBytes;

  Utils::MemCopyToPattern(m_sOldBytes, m_pDestination, m_dwCountNewBytes);
}

C_Patch::~C_Patch()
{
  if (m_bPatched)
  {
    Restore();
  }
}

bool C_Patch::Apply()
{
  if (m_bPatched)
    return false;
  if (m_pDestination == NULL)
    return false;
  if (m_sNewBytes.length() < 2)
    return false;

  string newBytes;
  Utils::PatternToHexString(m_sNewBytes, newBytes);

  bool bApplied = false;
  if (m_dwCountNewBytes > 0)
  {
    DWORD dwOldProtect;

    bApplied = true;
    bApplied &= (bool)VirtualProtect(m_pDestination, m_dwCountNewBytes, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    if (bApplied)
    {
      memcpy(m_pDestination, newBytes.c_str(), m_dwCountNewBytes);
      //DWORD dwTempProtect;
      //bApplied &= (bool)VirtualProtect(m_pDestination, m_dwCountNewBytes, dwOldProtect, &dwTempProtect);
    }
    else
    {
      if (C_CheatMgr::Instance->user.bDebugInformation)
      {
        cout << XS("Patch ") << m_sName << XS(" applying error: ") << hex << GetLastError() << endl;
      }
    }
  }

  if (C_CheatMgr::Instance->user.bDebugInformation && !bApplied)
  {
    cout << XS("Patch ") << m_sName << XS(" was not applied!") << endl;
  }

  m_bPatched = bApplied;

  return bApplied;
}

bool C_Patch::Restore()
{
  if (!m_bPatched)
    return false;
  if (m_pDestination == NULL)
    return false;
  if (m_sOldBytes.length() < 2)
    return false;

  string oldBytes;
  Utils::PatternToHexString(m_sOldBytes, oldBytes);

  bool bRestored = false;
  if (m_dwCountOldBytes > 0)
  {
    DWORD dwOldProtect;

    bRestored = true;
    bRestored &= (bool)VirtualProtect(m_pDestination, m_dwCountOldBytes, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    if (bRestored)
    {
      memcpy(m_pDestination, oldBytes.c_str(), m_dwCountOldBytes);
      //DWORD dwTempProtect;
      //bRestored &= (bool)VirtualProtect(m_pDestination, m_dwCountOldBytes, dwOldProtect, &dwTempProtect);
    }
    else
    {
      if (C_CheatMgr::Instance->user.bDebugInformation)
      {
        cout << XS("Patch ") << m_sName << XS(" restoring error: ") << hex << GetLastError() << endl;
      }
    }
  }

  if (C_CheatMgr::Instance->user.bDebugInformation && !bRestored)
  {
    cout << XS("Patch ") << m_sName << XS(" was not restored!") << endl;
  }

  m_bPatched = !bRestored;

  return bRestored;
}

bool C_Patch::SetDestination(void* newDst)
{
  if (newDst == NULL)
    return false;

  m_pDestination = newDst;

  return true;
}

bool C_Patch::SetName(const string &newName)
{
  if (newName.empty())
    return false;

  m_sName = newName;

  return true;
}

bool C_Patch::SetOldBytes(const string &oldBytes)
{
  if (oldBytes.length() < 2)
    return false;

  m_sOldBytes = oldBytes;
  m_dwCountOldBytes = Utils::CountPatternBytes(oldBytes);

  return (m_dwCountOldBytes > 0);
}

bool C_Patch::SetNewBytes(const string &newBytes)
{
  if (newBytes.length() < 2)
    return NULL;

  m_sNewBytes = newBytes;
  m_dwCountNewBytes = Utils::CountPatternBytes(newBytes);

  return (m_dwCountNewBytes > 0);
}

bool C_Patch::SetCountOldBytes(DWORD newCountOldBytes)
{
  m_dwCountOldBytes = newCountOldBytes;
  return true;
}

bool C_Patch::SetCountNewBytes(DWORD newCountNewBytes)
{
  m_dwCountNewBytes = newCountNewBytes;
  return true;
}

void* C_Patch::GetDestination() const
{
  return m_pDestination;
}

string C_Patch::GetName() const
{
  return m_sName;
}

DWORD C_Patch::GetCountOldBytes() const
{
  return m_dwCountOldBytes;
}

DWORD C_Patch::GetCountNewBytes() const
{
  return m_dwCountNewBytes;
}
