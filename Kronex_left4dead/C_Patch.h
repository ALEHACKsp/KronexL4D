#pragma once

class C_Patch
{
public:
  C_Patch(const string &name, void* dst, const string &newBytes);
  ~C_Patch();

  void* GetDestination() const;

  string GetName() const;

  DWORD GetCountOldBytes() const;
  DWORD GetCountNewBytes() const;

  bool SetDestination(void* newDst);
  bool SetName(const string &newName);
  bool SetOldBytes(const string &oldBytes);
  bool SetCountOldBytes(DWORD newCountOldBytes);
  bool SetNewBytes(const string &newBytes);
  bool SetCountNewBytes(DWORD newCountNewBytes);

  bool Apply();
  bool Restore();

private:
  string m_sName;
  void* m_pDestination;

  string m_sOldBytes;
  DWORD m_dwCountOldBytes;

  string m_sNewBytes;
  DWORD m_dwCountNewBytes;

  bool m_bPatched;
};

