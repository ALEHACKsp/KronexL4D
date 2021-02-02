#include "KronexMain.h"

C_Player::C_Player(C_EntityMgr* entityManager, int playerIndex, DWORD entityStartAddress, DWORD entityStructSize)
{
	pCMgr = C_CheatMgr::Instance;
  pEMgr = entityManager;

  m_dwBase = 0;
  dwJumpVelocity = 0x68; // 0x68
  dwTeam = 0xBC; // 0xBC
  dwHealth = 0xC4; // 0xC4
  dwFlag = 0xC8; // 0xC8
  dwYDiff = 0xD4; // 0xD4
  dwVelocity = 0xD8; // 0xD8
  dwPosition = 0xFC; // 0xFC // 0xE80
  //dwCharType = 0x118; // 0x118
  dwLifeStatus = 0x11F; // 0x11F
  dwIsSpawned = 0x1BC; // 0x1BC
  dwBoneMatrix = 0x660; // 0x660, 0x894, 0x8A4
  dwTickBase = 0x1248; // 0x1248
  dwMaxSpeed = 0x1150; // 0x1150
  dwMaxHealth = 0x1CA8; // 0x1CA8
  dwTankFrustration = 0x22D4; // 0x22D4
  dwIncapped = 0x1B7D; // 0x1B7D
  dwszLastPlaceName = 0x13C0; // 0x13C0 // length 12
  dwActiveWeapon = 0xE1C; // 0xE1C
  dwObserverTarget = 0x11A0; // 0x11A0

  mdwCurWeapID_Offsets[0] = 0x15D8; // 0x15D8
  mdwCurWeapID_Offsets[1] = 0x6C; // 0x6C

  mdwCharType_Offsets[0] = 0x72C; // 0x24
  mdwCharType_Offsets[1] = 0x20C; //  0x20
  //mdwCharType_Offsets[0] = 0x24; // 0x24
  //mdwCharType_Offsets[1] = 0x20; //  0x20
  //mdwCharType_Offsets[2] = 0x250; // 0x250

  mdwClassID_Offsets[0] = 0x8; // 0x8
  mdwClassID_Offsets[1] = 0x8; // 0x8
  mdwClassID_Offsets[2] = 0x1; // 0x1
  mdwClassID_Offsets[3] = 0x14; // 0x14

  mflAngleToTarget[0] = 0.0f;
  mflAngleToTarget[1] = 0.0f;
  mflAngleToTarget[2] = 0.0f;

  mflCurrentBonePos[0] = 0.0f;
  mflCurrentBonePos[1] = 0.0f;
  mflCurrentBonePos[2] = 0.0f;

	SetIndex(playerIndex);
  SetEntityListStartAddress(entityStartAddress);
  SetEntityStructSize(entityStructSize);

  UpdateBase();
}

C_Player::~C_Player()
{

}

float C_Player::Velocity(int coordType)
{
  if (!IsValid()) return 0.0f;
  if (coordType < 0 || coordType > 2) return 0.0f;
  return *(float*)(dwVelocity + m_dwBase + coordType * sizeof(float));
}

bool C_Player::Equals(C_Player* otherPlayer)
{
  if (GetBase() == otherPlayer->GetBase()) return true;
  return false;
}

DWORD C_Player::GetStartAddress()
{
  return dwEntListStartAdr;
}

bool C_Player::SetIndex(int newIndex)
{
  if (newIndex < 0) return false;
  m_iIndex = newIndex;
  return true;
}

int C_Player::GetIndex()
{
  return m_iIndex;
}

bool C_Player::SetEntityListStartAddress(DWORD newEntListStartAdr)
{
  if (newEntListStartAdr <= 0) return false;
  dwEntListStartAdr = newEntListStartAdr;
  return true;
}

bool C_Player::SetEntityStructSize(DWORD newEntStructSize)
{
  if (newEntStructSize <= 0) return false;
  dwEntStructSize = newEntStructSize;
  return true;
}

bool C_Player::UpdateBase(DWORD newBaseAddress)
{
  if (newBaseAddress <= 0)
  {
    m_dwBase = *(DWORD*)(pCMgr->dwClientDll + dwEntListStartAdr + m_iIndex * dwEntStructSize);
    if (m_dwBase != 0) return true;
    return false;
  }
  m_dwBase = newBaseAddress;
  return true;
}

C_CheatMgr* C_Player::CManager()
{
	return pCMgr;
}

C_EntityMgr* C_Player::EManager()
{
	return pEMgr;
}

float* C_Player::GetAngle()
{
	return mflAngleToTarget;
}

float* C_Player::CalculateAngleTo(C_Player* target, int bone)
{
  if (target == 0 || !target->IsValid()) return mflAngleToTarget;

	float* thisPos;
	float* targetPos;

  float delta[3];

  thisPos = this->BonePos(bone);
  //targetPos = target->BonePos(11);
  targetPos = target->Position();

  delta[0] = targetPos[0] - thisPos[0];
  delta[1] = targetPos[1] - thisPos[1];
  delta[2] = targetPos[2] - thisPos[2] + target->YDiff() + 2.0f;

	float hypotenuse = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
  mflAngleToTarget[0] = (float)(atan(delta[2] / hypotenuse) * 57.295779513082f); // 57.295779513082f == (180.0f / PI)
  mflAngleToTarget[1] = (float)(atan(delta[1] / delta[0]) * 57.295779513082f); // 57.295779513082f == (180.0f / PI)
  mflAngleToTarget[2] = 0.0f;

	if (delta[0] >= 0.0f && delta[1] < 0.0f) mflAngleToTarget[1] += 180.0f;
  else if (delta[0] >= 0.0f && delta[1] >= 0.0f) mflAngleToTarget[1] -= 180.0f;

	return mflAngleToTarget;
}

float C_Player::DistanceTo(C_Player* player)
{
	if (player == 0 || !player->IsValid()) return 0.0f;
	return Utils::Get3dDistance(this->Position(), player->Position());
}

bool C_Player::IsValid()
{
  return UpdateBase();
}

DWORD C_Player::GetBase()
{
	return m_dwBase;
}

CBaseEntity* C_Player::BaseEntity()
{
  return (CBaseEntity*)m_dwBase;
}

string C_Player::Nickname()
{
  if (!IsValid()) return string();

  pinfo_s pInfo;
  g_pEngineClient->GetPlayerInfo(m_iIndex + 1, &pInfo);
  return string(pInfo.name - 8);
}

int C_Player::Flag()
{
  if (!IsValid()) return FLAG_UNKNOWN;
  return (int)*(int*)(m_dwBase + dwFlag);
}

bool C_Player::Incapped()
{
  if (!IsValid()) return false;
  if (*(byte*)(m_dwBase + dwIncapped) == (byte)1) return true;
  return false;
}

int C_Player::TankFrustration()
{
  if (!IsValid()) return -1;
  return 100 - *(int*)(m_dwBase + dwTankFrustration);
}

CBaseHandle C_Player::ActiveWeapon()
{
  if (!IsValid()) return NULL;
  return *(CBaseHandle*)(m_dwBase + dwActiveWeapon);
}

CBaseHandle C_Player::ObserverTarget()
{
  if (!IsValid()) return NULL;
  return *(CBaseHandle*)(m_dwBase + (DWORD)dwObserverTarget);
}

int C_Player::TickBase()
{
  if (!IsValid()) return NULL;
  return *(int*)(m_dwBase + dwTickBase);
}

int C_Player::Team()
{
  if (!IsValid()) return TEAM_INVALID;
  //return *(int*)(m_dwBase + dwTeam);

  switch (CurWeapID())
  {
    case WEAPON_ID_INVALID:
      return TEAM_INVALID;

    case WEAPON_ID_TANK_CLAW:
    case WEAPON_ID_HUNTER_CLAW:
    case WEAPON_ID_BOOMER_CLAW:
    case WEAPON_ID_SMOKER_CLAW:
      return TEAM_INFECT;

    case WEAPON_ID_SPECTATOR:
      return TEAM_SPEC;

    default:
      return TEAM_SURV;
  }

  switch (ClassID())
  {
    case ClassID_Unknown:
    {
      return TEAM_INVALID;
    }
    case ClassID_Boomer:
    case ClassID_Hunter:
    case ClassID_Tank:
    case ClassID_Smoker:
    case ClassID_BoomerClaw:
    case ClassID_HunterClaw:
    case ClassID_TankClaw:
    case ClassID_SmokerClaw:
    case ClassID_Infected:
    {
      return TEAM_INFECT;
    }
    case ClassID_TerrorPlayer:
    case ClassID_TerrorPlayerResource:
    case ClassID_SurvivorBot:
    case ClassID_TerrorWeapon:
    case ClassID_TerrorGun:
    case ClassID_SubMachinegun:
    case ClassID_SniperRifle:
    case ClassID_PumpShotgun:
    case ClassID_PropaneTank:
    case ClassID_Pistol:
    case ClassID_PipeBomb:
    case ClassID_PainPills:
    case ClassID_OxygenTank:
    case ClassID_PropMountedGun:
    case ClassID_Molotov:
    case ClassID_PropMinigun:
    case ClassID_GasCan:
    case ClassID_FirstAidKit:
    case ClassID_BaseShotgun:
    case ClassID_AutoShotgun:
    case ClassID_AssaultRifle:
    case ClassID_TerrorViewModel:
    case ClassID_SurvivorRescue:
    case ClassID_CSPlayer:
    {
      return TEAM_SURV;
    }

    default:
    {
      return TEAM_SPEC;
    }
  }
}

bool C_Player::SetTeam(int newTeamNum)
{
  if (!IsValid()) return false;
  *(int*)(m_dwBase + dwTeam) = (int)newTeamNum;
  return true;
}

int C_Player::Health()
{
  if (!IsValid()) return -1;
  return *(int*)(m_dwBase + dwHealth);
}

int C_Player::MaxHealth()
{
  if (!IsValid()) return -1;
  return *(int*)(m_dwBase + dwMaxHealth);
}

ClassIds C_Player::ClassID()
{
  if (!IsValid()) return ClassIds::ClassID_Unknown;

  DWORD* p1 = (DWORD*)(m_dwBase + mdwClassID_Offsets[0]);
  if (p1 > (DWORD*)0xFFFF)
  {
    DWORD* p2 = (DWORD*)(*p1 + mdwClassID_Offsets[1]);
    if (p2 > (DWORD*)0xFFFF)
    {
      DWORD* p3 = (DWORD*)(*p2 + mdwClassID_Offsets[2]);
      if (p3 > (DWORD*)0xFFFF)
      {
        ClassIds* p4 = (ClassIds*)(*p3 + mdwClassID_Offsets[3]);
        if (p4 > (ClassIds*)0xFFFF)
        {
          return *p4;
        }
      }
    }
  }
  return ClassID_Unknown;
}

float C_Player::JumpVelocity()
{
  if (!IsValid()) return 0.0f;
  return *(float*)(m_dwBase + dwJumpVelocity);
}

float C_Player::YDiff()
{
  if (!IsValid()) return 0.0f;
  return *(float*)(m_dwBase + dwYDiff);
}

float* C_Player::Position()
{
  if (!IsValid()) return mflCurrentBonePos;
  return (float*)(m_dwBase + dwPosition);
}

bool C_Player::IsAlive()
{
  if (!IsValid()) return false;

  if (*(byte*)(m_dwBase + dwLifeStatus) == (byte)0 && Health() > 0) return true;
  return false;
}

bool C_Player::IsSpawned()
{
  if (!IsValid()) return false;
  if (*(int*)(m_dwBase + dwIsSpawned) == 1) return true;
	else return false;
}

float* C_Player::BonePos(int boneNum)
{
  if (boneNum < 0 || boneNum > 52) return mflCurrentBonePos;
  if (!IsValid()) return mflCurrentBonePos;

  if (m_dwBase == NULL) return mflCurrentBonePos;
  if (dwBoneMatrix == NULL) return mflCurrentBonePos;

  DWORD Matrix = *(DWORD*)(m_dwBase + dwBoneMatrix);
  if (Matrix == NULL) return mflCurrentBonePos;

  mflCurrentBonePos[0] = *(float*)(Matrix + boneNum * 0x30 + 0x0C);
  mflCurrentBonePos[1] = *(float*)(Matrix + boneNum * 0x30 + 0x1C);
  mflCurrentBonePos[2] = *(float*)(Matrix + boneNum * 0x30 + 0x2C);

  // smart fixes for fucking l4d1
  int stableBone = 11; // 10
  float tempPos[3];
  tempPos[0] = mflCurrentBonePos[0];
  tempPos[1] = mflCurrentBonePos[1];
  tempPos[2] = mflCurrentBonePos[2];
  if (boneNum != stableBone
    && (Utils::Get3dDistance(tempPos, BonePos(stableBone)) > 110.0f
        || ((mflCurrentBonePos[0] == 0.0f && mflCurrentBonePos[1] == 0.0f)
          || (mflCurrentBonePos[0] == 0.0f && mflCurrentBonePos[2] == 0.0f)
          || (mflCurrentBonePos[1] == 0.0f && mflCurrentBonePos[2] == 0.0f))))
  {
    mflCurrentBonePos[0] = *(float*)(Matrix + stableBone * 0x30 + 0x0C);
    mflCurrentBonePos[1] = *(float*)(Matrix + stableBone * 0x30 + 0x1C);
    mflCurrentBonePos[2] = *(float*)(Matrix + stableBone * 0x30 + 0x2C);
  }
  else
  {
    mflCurrentBonePos[0] = tempPos[0];
    mflCurrentBonePos[1] = tempPos[1];
    mflCurrentBonePos[2] = tempPos[2];
  }

  return mflCurrentBonePos;
}

float C_Player::MaxSpeed()
{
  if (!IsValid()) return 0.0f;
  return *(float*)(m_dwBase + dwMaxSpeed);
}

int C_Player::CurWeapID()
{
  if (!IsValid()) return WEAPON_ID_INVALID;
  return (int)*(int*)(*(DWORD*)(m_dwBase + mdwCurWeapID_Offsets[0]) + mdwCurWeapID_Offsets[1]);
}

int C_Player::CharType()
{
  //return (int)*(int*)(*(DWORD*)(*(DWORD*)(dwBase + mdwCharType_Offsets[0]) + mdwCharType_Offsets[1]) + mdwCharType_Offsets[2]);
  //return *(int*)(dwCharType + dwBase);

  //if (!IsValid()) return CHARACTER_TYPE_INVALID;
  //return *(int*)(*(DWORD*)(dwBase + mdwCharType_Offsets[0]) + mdwCharType_Offsets[1]);

  if (!IsValid()) return CHARACTER_TYPE_INVALID;

  switch (CurWeapID())
  {
    case WEAPON_ID_INVALID:
      return CHARACTER_TYPE_INVALID;

    case WEAPON_ID_TANK_CLAW:
      return CHARACTER_TYPE_TANK;

    case WEAPON_ID_HUNTER_CLAW:
      return CHARACTER_TYPE_HUNTER;

    case WEAPON_ID_BOOMER_CLAW:
      return CHARACTER_TYPE_BOOMER;

    case WEAPON_ID_SMOKER_CLAW:
      return CHARACTER_TYPE_SMOKER;

    case WEAPON_ID_SPECTATOR:
      return CHARACTER_TYPE_SPEC;

    default:
      return CHARACTER_TYPE_SURV;
  }
}
