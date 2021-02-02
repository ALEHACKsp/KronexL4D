#pragma once

class C_VMTHook
{
public:
  C_VMTHook(const string &sName, void* pVMTObject, int iFnIndex, void* pHkFunction);
  ~C_VMTHook();

  string GetName() const;

  void* GetVMTObject() const;
  void* GetOriginFn() const;
  template<class T> T GetOriginFn() const { return (T)GetOriginFn(); }
  void* GetHookFn() const;

  int GetFnIndex() const;

  bool SetName(const string &sNewName);
  bool SetVMTObject(void* pNewVMTObject);
  bool SetOriginFn(void* pNewOriginFn);
  bool SetHookFn(void* pNewHookFn);
  bool SetFnIndex(int iNewFnIndex);

  bool Apply();
  bool Restore();

private:
  string m_sName;

  void* m_pVMTObject;
  void* m_pOriginFn;
  void* m_pHookFn;

  int m_iFnIndex;

  bool m_bHooked;
};

