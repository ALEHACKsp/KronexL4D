#include "KronexMain.h"

C_VMTHookMgr* C_VMTHookMgr::_Instance = NULL;

C_VMTHookMgr* C_VMTHookMgr::Instance()
{
  if (!_Instance)
  {
    _Instance = new C_VMTHookMgr;
  }
  return _Instance;
}

C_VMTHookMgr::C_VMTHookMgr()
{

}

C_VMTHookMgr::~C_VMTHookMgr()
{
  for (auto iterator = m_mapHooks.begin(); iterator != m_mapHooks.end(); ++iterator)
  {
    delete iterator->second;
  }
  m_mapHooks.clear();
}

bool C_VMTHookMgr::AddStdVMTHook(
  void* pVMTObject,
  void* pStdFunction,
  int iMaxFunctionsCount,
  void* pHkFunction,
  const string &hookName)
{
  if (pVMTObject == NULL)
    return false;
  if (pHkFunction == NULL)
    return false;
  if (pStdFunction == NULL)
    return false;
  if (hookName.empty())
    return false;

  for (int i = 0; i < iMaxFunctionsCount; i++)
  {
    if (((void**)pVMTObject)[0] == pStdFunction)
    {
      return AddVMTHook(pVMTObject, i, pHkFunction, hookName);
    }
  }
  return false;
}

bool C_VMTHookMgr::AddVMTHook(
  void* pVMTObject,
  int iFnIndex,
  void* pHkFunction,
  const string &hookName)
{
  C_VMTHookMgr* pVMTHookMgr = Instance();

  if (pVMTObject == NULL)
    return false;
  if (pHkFunction == NULL)
    return false;
  if (iFnIndex < 0)
    return false;
  if (hookName.empty())
    return false;

  pVMTHookMgr->m_mapHooks.insert(
    pair<string, C_VMTHook*>(hookName, new C_VMTHook(hookName, pVMTObject, iFnIndex, pHkFunction)));
  return true;
}

bool C_VMTHookMgr::DeleteVMTHook(const string &hookName)
{
  C_VMTHookMgr* pVMTHookMgr = Instance();

  if (pVMTHookMgr->m_mapHooks.empty())
    return false;
  if (hookName.empty())
    return false;

  auto iterator = pVMTHookMgr->m_mapHooks.find(hookName);
  if (iterator == pVMTHookMgr->m_mapHooks.end())
    return false;

  delete iterator->second;
  pVMTHookMgr->m_mapHooks.erase(iterator);

  return true;
}

bool C_VMTHookMgr::ApplyHook(const string &hookName)
{
  C_VMTHookMgr* pVMTHookMgr = Instance();

  if (pVMTHookMgr->m_mapHooks.empty())
    return false;
  if (hookName.empty())
    return false;

  auto iterator = pVMTHookMgr->m_mapHooks.find(hookName);
  if (iterator == pVMTHookMgr->m_mapHooks.end())
    return false;

  return iterator->second->Apply();
}

bool C_VMTHookMgr::RestoreHook(const string &hookName)
{
  C_VMTHookMgr* pVMTHookMgr = Instance();

  if (pVMTHookMgr->m_mapHooks.empty())
    return false;
  if (hookName.empty())
    return false;

  auto iterator = pVMTHookMgr->m_mapHooks.find(hookName);
  if (iterator == pVMTHookMgr->m_mapHooks.end())
    return false;

  return iterator->second->Restore();
}

C_VMTHook* C_VMTHookMgr::GetHook(const string &hookName)
{
  C_VMTHookMgr* pVMTHookMgr = Instance();

  if (pVMTHookMgr->m_mapHooks.empty())
    return NULL;
  if (hookName.empty())
    return NULL;

  auto iterator = pVMTHookMgr->m_mapHooks.find(hookName);
  if (iterator == pVMTHookMgr->m_mapHooks.end())
    return NULL;

  return iterator->second;
}