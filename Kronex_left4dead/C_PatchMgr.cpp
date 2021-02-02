#include "KronexMain.h"

C_PatchMgr* C_PatchMgr::_Instance = NULL;

C_PatchMgr* C_PatchMgr::Instance()
{
  if (!_Instance)
  {
    _Instance = new C_PatchMgr;
  }
  return _Instance;
}

C_PatchMgr::C_PatchMgr()
{
  
}

C_PatchMgr::~C_PatchMgr()
{
  for (auto iterator = patches.begin(); iterator != patches.end(); ++iterator)
  {
    delete iterator->second;
  }
  patches.clear();
}

bool C_PatchMgr::RegPatch(void* dst, const string &newBytes, const string &patchName)
{
  C_PatchMgr* pPatchMgr = Instance();

  if (dst == NULL)
    return false;
  if (newBytes.length() < 2)
    return false;
  if (patchName.empty())
    return false;

  pPatchMgr->patches.insert(
    pair<string, C_Patch*>(patchName, new C_Patch(patchName, dst, newBytes)));
  return true;
}

bool C_PatchMgr::UnRegPatch(const string &patchName)
{
  C_PatchMgr* pPatchMgr = Instance();

  if (pPatchMgr->patches.empty())
    return false;
  if (patchName.empty())
    return false;

  auto iterator = pPatchMgr->patches.find(patchName);
  if (iterator == pPatchMgr->patches.end())
    return false;

  delete iterator->second;
  pPatchMgr->patches.erase(iterator);

  return true;
}

bool C_PatchMgr::ApplyPatch(const string &patchName)
{
  C_PatchMgr* pPatchMgr = Instance();

  if (pPatchMgr->patches.empty())
    return false;
  if (patchName.empty())
    return false;

  auto iterator = pPatchMgr->patches.find(patchName);
  if (iterator == pPatchMgr->patches.end())
    return false;

  return iterator->second->Apply();
}

bool C_PatchMgr::RestorePatch(const string &patchName)
{
  C_PatchMgr* pPatchMgr = Instance();

  if (pPatchMgr->patches.empty())
    return false;
  if (patchName.empty())
    return false;

  auto iterator = pPatchMgr->patches.find(patchName);
  if (iterator == pPatchMgr->patches.end())
    return false;

  return iterator->second->Restore();
}

C_Patch* C_PatchMgr::GetPatch(const string &patchName)
{
  C_PatchMgr* pPatchMgr = Instance();

  if (pPatchMgr->patches.empty())
    return NULL;
  if (patchName.empty())
    return false;

  auto iterator = pPatchMgr->patches.find(patchName);
  if (iterator == pPatchMgr->patches.end())
    return NULL;

  return iterator->second;
}
