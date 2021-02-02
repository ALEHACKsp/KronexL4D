#include "KronexMain.h"

C_CVarMgr* C_CVarMgr::_Instance = NULL;

C_CVarMgr* C_CVarMgr::Instance()
{
  if (!_Instance)
  {
    _Instance = new C_CVarMgr;
  }
  return _Instance;
}

C_CVarMgr::C_CVarMgr()
{

}

C_CVarMgr::~C_CVarMgr()
{
  ConVar* conVar;
  for (auto iterator = m_mapCVars.begin(); iterator != m_mapCVars.end(); ++iterator)
  {
    conVar = iterator->second;
    g_pCVar->UnregisterConCommand(conVar);

    delete[] conVar->GetBaseName();
    delete[] conVar->GetDefault();
    delete conVar;
  }
  m_mapCVars.clear();

  for (auto iterator = m_mapInternalChangedCVars.begin(); iterator != m_mapInternalChangedCVars.end(); ++iterator)
  {
    RestoreInternalValue(iterator->second->m_sCvarName);
  }
  m_mapInternalChangedCVars.clear();
}

bool C_CVarMgr::SetInternalValue(const string &varName, const string &newValue)
{
  C_CVarMgr* pCVarMgr = Instance();

  if (varName.empty())
    return false;
  if (newValue.empty())
    return false;
  
  auto iterator = pCVarMgr->m_mapInternalChangedCVars.find(varName);
  if (iterator != pCVarMgr->m_mapInternalChangedCVars.end())
  {
    if (RestoreInternalValue(varName))
    {
      pCVarMgr->m_mapInternalChangedCVars.erase(iterator);
    }
    else
    {
      cout << "RestoreInternalValue fails :(" << endl;
      return false;
    }
  }
  
  ConVar* pCvar = FindVar(varName);

  if (pCvar)
  {
    ValueTypes valueType = Utils::GetValueType(newValue);

    InternalChangedCvar* pChangedCvar = new InternalChangedCvar(varName, pCvar, valueType);

    switch (valueType)
    {
      case IntValue:
      {
        pChangedCvar->m_sDefaultInternalValue = to_string(pCvar->m_nValue);
        
        pCvar->m_nValue = stoi(newValue);

        pCVarMgr->m_mapInternalChangedCVars.insert(
          pair<string, InternalChangedCvar*>(varName, pChangedCvar));
        return true;
      }
      case FloatValue:
      {
        pChangedCvar->m_sDefaultInternalValue = to_string(pCvar->m_fValue);

        pCvar->m_fValue = stof(newValue);

        pCVarMgr->m_mapInternalChangedCVars.insert(
          pair<string, InternalChangedCvar*>(varName, pChangedCvar));
        return true;
      }
      case StringValue:
      {
        pChangedCvar->m_sDefaultInternalValue = pCvar->m_pszString;

        strcpy(pCvar->m_pszString, newValue.c_str());

        pCVarMgr->m_mapInternalChangedCVars.insert(
          pair<string, InternalChangedCvar*>(varName, pChangedCvar));
        return true;
      }
      case UnknownValue:
      default:
      {
        if (C_CheatMgr::Instance->user.bDebugInformation)
        {
          cout << XS("SetInternalValue(") << varName << XS(", ") << newValue << XS(") failed! Unknown value type!") << endl;
        }
        delete pChangedCvar;
        return false;
      }
    }
  }
  return false;
}

bool C_CVarMgr::RestoreInternalValue(const string &varName)
{
  C_CVarMgr* pCVarMgr = Instance();

  if (varName.empty())
    return false;

  auto iterator = pCVarMgr->m_mapInternalChangedCVars.find(varName);
  if (iterator == pCVarMgr->m_mapInternalChangedCVars.end())
    return true;

  InternalChangedCvar* pChangedCvar = iterator->second;

  ValueTypes valueType = pChangedCvar->m_valueType;

  switch (valueType)
  {
    case IntValue:
    {
      pChangedCvar->m_pValveCvar->m_nValue = stoi(pChangedCvar->m_sDefaultInternalValue);
      break;
    }
    case FloatValue:
    {
      pChangedCvar->m_pValveCvar->m_fValue = stof(pChangedCvar->m_sDefaultInternalValue);
      break;
    }
    case StringValue:
    {
      strcpy(pChangedCvar->m_pValveCvar->m_pszString, pChangedCvar->m_sDefaultInternalValue.c_str());
      break;
    }
    case UnknownValue:
    default:
    {
      if (C_CheatMgr::Instance->user.bDebugInformation)
      {
        cout << XS("RestoreInternalValue(") << varName << XS(") failed! Unknown value type!") << endl;
      }
      return false;
    }
  }

  delete pChangedCvar;
  return true;
}

ConVar* C_CVarMgr::RegConVar(
  const string &varName,
  const string &varDefaultValue,
  int flags,
  FnChangeCallback_t callback)
{
  C_CVarMgr* pCVarMgr = Instance();

  if (!g_pCVar)
    return NULL;
  if (varName.empty())
    return NULL;

  auto iterator = pCVarMgr->m_mapCVars.find(varName);
  if (iterator != pCVarMgr->m_mapCVars.end())
    return NULL;

  char* tempVarName = new char[varName.length() + 1];
  memcpy(tempVarName, varName.c_str(), varName.length() + 1);

  char* tempDefVal = new char[varDefaultValue.length() + 1];
  memcpy(tempDefVal, varDefaultValue.c_str(), varDefaultValue.length() + 1);

  ConVar* conVar = new ConVar(tempVarName, tempDefVal, flags);
  g_pCVar->RegisterConCommand(conVar);

  if (callback)
  {
    conVar->InstallChangeCallback(callback);
  }

  pCVarMgr->m_mapCVars.insert(pair<string, ConVar*>(varName, conVar));
  return conVar;
}

bool C_CVarMgr::UnRegConVar(const string &varName)
{
  C_CVarMgr* pCVarMgr = Instance();

  if (!g_pCVar)
    return false;
  if (varName.empty())
    return false;

  auto iterator = pCVarMgr->m_mapCVars.find(varName);
  if (iterator == pCVarMgr->m_mapCVars.end())
    return false;

  ConVar* conVar = iterator->second;
  g_pCVar->UnregisterConCommand(conVar);

  delete [] conVar->GetBaseName();
  delete [] conVar->GetDefault();
  delete conVar;

  pCVarMgr->m_mapCVars.erase(iterator);

  return true;
}

ConVar* C_CVarMgr::FindVar(const string &varName)
{
  C_CVarMgr* pCVarMgr = Instance();

  if (!g_pCVar)
    return NULL;
  if (varName.empty())
    return NULL;

  auto iterator = pCVarMgr->m_mapCVars.find(varName);
  if (iterator == pCVarMgr->m_mapCVars.end())
  {
    ConVar* convar = g_pCVar->FindVar(varName.c_str());

    if (convar == NULL)
    {
      if (C_CheatMgr::Instance->user.bDebugInformation)
      {
        cout << XS("ConVar ") << varName << XS(" not found!") << endl;
      }
      return NULL;
    }

    return convar;
  }

  return iterator->second;
}
