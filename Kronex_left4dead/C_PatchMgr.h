#pragma once

class C_PatchMgr
{
public:
  ~C_PatchMgr();

  static C_PatchMgr* Instance();

  static bool RegPatch(void* dst, const string &newBytes, const string &patchName);
  static bool UnRegPatch(const string &patchName);
  static bool ApplyPatch(const string &patchName);
  static bool RestorePatch(const string &patchName);

  static C_Patch* GetPatch(const string &patchName);

private:
  C_PatchMgr();

  static C_PatchMgr* _Instance;

  map<string, C_Patch*> patches;
};

