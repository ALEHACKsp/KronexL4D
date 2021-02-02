#pragma once

class InternalChangedCvar
{
public:
  InternalChangedCvar(
    const string &sName,
    ConVar* pCvar,
    ValueTypes valueType)
  : m_sCvarName(sName),
    m_pValveCvar(pCvar),
    m_valueType(valueType)
  {

  }

  string m_sCvarName;
  string m_sDefaultInternalValue;
  ConVar* m_pValveCvar;
  ValueTypes m_valueType;

};

class C_CVarMgr
{
public:
  ~C_CVarMgr();

  static C_CVarMgr* Instance();

  static ConVar* RegConVar(const string &varName, const string &varDefaultValue, int flags, FnChangeCallback_t callback = 0);
  static bool UnRegConVar(const string &varName);

  static ConVar* FindVar(const string &varName);
  static bool SetInternalValue(const string &varName, const string &newValue);
  static bool RestoreInternalValue(const string &varName);

private:
  C_CVarMgr();

  static C_CVarMgr* _Instance;

  map<string, ConVar*> m_mapCVars;
  map<string, InternalChangedCvar*> m_mapInternalChangedCVars;
};

