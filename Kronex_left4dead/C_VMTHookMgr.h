#pragma once

class C_VMTHookMgr
{
public:
  ~C_VMTHookMgr();

  static C_VMTHookMgr* Instance();

  static bool AddVMTHook(void* pVMTObject, int iFnIndex, void* pHkFunction, const string &hookName);
  static bool AddStdVMTHook(void* pVMTObject, void* pStdFunction, int iMaxFunctionsCount, void* pHkFunction, const string &hookName);
  static bool DeleteVMTHook(const string &hookName);
  static bool ApplyHook(const string &hookName);
  static bool RestoreHook(const string &hookName);

  static C_VMTHook* GetHook(const string &hookName);

private:
  C_VMTHookMgr();

  static C_VMTHookMgr* _Instance;

  map<string, C_VMTHook*> m_mapHooks;
};

