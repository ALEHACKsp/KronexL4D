#pragma once

class Account
{
public:

	string sName;
  bool bDebugInformation;

  string sSTEAMID;
  bool bSTEAMIDCheck;

	string sHWID;
  string sRootHWID;
  bool bHWIDCheck;

	const int iDate[3];
	const int iTime[3];
  bool bCheckExpireTime;

  int iCheats;

  string GetExpire()
  {
    string expire = XS("LIFETIME");
    if (bCheckExpireTime)
    {
      expire.clear();
      expire =
        to_string(iDate[0]) + XS("dd/") +
        to_string(iDate[1]) + XS("mm/") +
        to_string(iDate[2]) + XS("yy ") +
        to_string(iTime[0]) + XS("h:") +
        to_string(iTime[1]) + XS("m:") +
        to_string(iTime[2]) + XS("s");
    }
    return expire;
  }
};

const Account ACC_ASTARION	=
{
  XS("Astarion"), true,
  XS("76561198078455299"), false,
  XS("465865f41f1adf9a65d4f030777969f024a80fc1d6eb812253f9405f76995dc8"),
  XS("7035ff4c251bb69edbf7724271a8eb9e7f62f25f37c999fd06d5a959f0237427"), true,
  { 14, 10, 2017 }, { 15, 16, 0 }, false,
  CH_ALL
};

const Account ACC_KPUOH =
{
  XS("KpuoH"), true,
  XS("76561198078455299"), false,
  XS("df486dd34b997658c477cb14f9613913fe3ba3474d8040ec8bb9d22a0fb99e24"),
  XS("df486dd34b997658c477cb14f9613913fe3ba3474d8040ec8bb9d22a0fb99e24"), false,
  { 21, 1, 2018 }, { 13, 54, 0 }, true,
  CH_ALL
};

const Account ACC_INVIRICO =
{
  XS("Invisible_Ricoshet"), false,
  XS("76561197993648040"), false,
  XS("c9a974db34f3e8a03b065fd3e00d5d67953197729edbf225c2c6e657b16d1736"),
  XS("c9a974db34f3e8a03b065fd3e00d5d67953197729edbf225c2c6e657b16d1736"), true,
  { 14, 11, 2017 }, { 15, 16, 0 }, true,
  CH_ALL
};

const Account ACC_SIMPLYNOOB =
{
  XS("$2000 for 1 cigarette"), true,
  XS("76561197993648040"), false,
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"),
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"), false,
  { 14, 10, 2017 }, { 15, 16, 0 }, false,
  CH_ALL
};

const Account ACC_HELIX =
{
  XS("Andrey"), true,
  XS("76561198096721454"), true,
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"),
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"), false,
  { 14, 10, 2017 }, { 15, 16, 0 }, false,
  CH_ALL
};

const Account ACC_RZN =
{
  XS("rzn"), false,
  XS("76561198175419355"), true,
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"),
  XS("4d4028360a3f8aecf1a2fee4bcecd04592985aee8a75d6ca085e8b74321af4a5"), false,
  { 12, 10, 2017 }, { 0, 0, 0 }, true,
  CH_ALL
};

const Account ACC_VOTARY =
{
  XS("Votary"), false,
  XS("76561198209099120"), false,
  XS("8b5051413919759370f4e8199ff971111af48edb4f766b39041ecca0211de75d"),
  XS("f2ff672e9526a0c07763e72499960ff0c583bdb617369f28095b6d763966de15"), true,
  { 1, 1, 2018 }, { 0, 0, 0 }, true,
  CH_ALL
};

