#include "KronexMain.h"

C_VMTHook::C_VMTHook(const string &sName, void* pVMTObject, int iFnIndex, void* pHkFunction)
  : m_sName(sName),
    m_pVMTObject(pVMTObject),
    m_pHookFn(pHkFunction),
    m_iFnIndex(iFnIndex),
    m_bHooked(false)
{
  if (m_pVMTObject)
  {
    if (m_iFnIndex >= 0)
    {
      m_pOriginFn = ((void***)m_pVMTObject)[0][m_iFnIndex];
    }
  }
}

C_VMTHook::~C_VMTHook()
{
  if (m_bHooked)
  {
    Restore();
  }
}

bool C_VMTHook::Apply()
{
  if (m_bHooked)
    return false;
  if (m_pVMTObject == NULL)
    return false;
  if (m_pHookFn == NULL)
    return false;

  DWORD dwOldProtect;
  bool bApplied = true;

  m_pOriginFn = ((void***)m_pVMTObject)[0][m_iFnIndex];

  bApplied &= (bool)VirtualProtect(&((void***)m_pVMTObject)[0][m_iFnIndex], sizeof(m_pHookFn), PAGE_EXECUTE_READWRITE, &dwOldProtect);
  if (bApplied)
  {
    ((void***)m_pVMTObject)[0][m_iFnIndex] = m_pHookFn;
    //DWORD dwTempProtect;
    //bApplied &= (bool)VirtualProtect(&((void***)m_pVMTObject)[0][m_iFnIndex], sizeof(m_pHookFn), dwOldProtect, &dwTempProtect);
  }
  else
  {
    if (C_CheatMgr::Instance->user.bDebugInformation)
    {
      cout << XS("VMTHook ") << m_sName << XS(" applying error: ") << hex << GetLastError() << endl;
    }
  }

  if (C_CheatMgr::Instance->user.bDebugInformation && !bApplied)
  {
    cout << XS("VMTHook ") << m_sName << XS(" was not applied!") << endl;
  }

  m_bHooked = bApplied;

  return bApplied;
}

bool C_VMTHook::Restore()
{
  if (!m_bHooked)
    return false;
  if (m_pVMTObject == NULL)
    return false;
  if (m_pOriginFn == NULL)
    return false;

  DWORD dwOldProtect;
  bool bRestored = true;

  bRestored &= (bool)VirtualProtect(&((void***)m_pVMTObject)[0][m_iFnIndex], sizeof(m_pOriginFn), PAGE_EXECUTE_READWRITE, &dwOldProtect);
  if (bRestored)
  {
    ((void***)m_pVMTObject)[0][m_iFnIndex] = m_pOriginFn;
    //DWORD dwTempProtect;
    //bRestored &= (bool)VirtualProtect(&((void***)m_pVMTObject)[0][m_iFnIndex], sizeof(m_pOriginFn), dwOldProtect, &dwTempProtect);
  }
  else
  {
    if (C_CheatMgr::Instance->user.bDebugInformation)
    {
      cout << XS("VMTHook ") << m_sName << XS(" restoring error: ") << hex << GetLastError() << endl;
    }
  }

  if (C_CheatMgr::Instance->user.bDebugInformation && !bRestored)
  {
    cout << XS("VMTHook ") << m_sName << XS(" was not restored!") << endl;
  }

  m_bHooked = !bRestored;

  return bRestored;
}

bool C_VMTHook::SetName(const string &sNewName)
{
  if (sNewName.empty())
    return false;

  m_sName = sNewName;
  return true;
}

bool C_VMTHook::SetVMTObject(void* pNewVMTObject)
{
  if (pNewVMTObject == NULL)
    return false;

  m_pVMTObject = pNewVMTObject;
  return true;
}

bool C_VMTHook::SetOriginFn(void* pNewOriginFn)
{
  if (pNewOriginFn == NULL)
    return false;

  m_pOriginFn = pNewOriginFn;
  return true;
}

bool C_VMTHook::SetHookFn(void* pNewHookFn)
{
  if (pNewHookFn == NULL)
    return false;

  m_pHookFn = pNewHookFn;
  return true;
}

bool C_VMTHook::SetFnIndex(int iNewFnIndex)
{
  if (iNewFnIndex < 0)
    return false;

  m_iFnIndex = iNewFnIndex;
  return true;
}

string C_VMTHook::GetName() const
{
  return m_sName;
}

void* C_VMTHook::GetVMTObject() const
{
  return m_pVMTObject;
}

void* C_VMTHook::GetOriginFn() const
{
  return m_pOriginFn;
}

void* C_VMTHook::GetHookFn() const
{
  return m_pHookFn;
}

int C_VMTHook::GetFnIndex() const
{
  return m_iFnIndex;
}
