#include "C_Player.h"

C_Player::C_Player(C_EntityManager* entityManager, int playerIndex, DWORD entityStartAddress, DWORD entityStructSize)
{
	m_pCManager = C_CheatManager::Instance;
  m_pEManager = entityManager;

  m_dwBase = 0;
  m_dwJumpVelocity = 0x68; // 0x68
  m_dwTeam = 0xBC; // 0xBC
  m_dwHealth = 0xC4; // 0xC4
  m_dwFlag = 0xC8; // 0xC8
  m_dwYDiff = 0xD4; // 0xD4
  m_dwPosition = 0xFC; // 0xFC // 0xE80
  m_dwLifeStatus = 0x11F; // 0x11F
  m_dwIsSpawned = 0x1BC; // 0x1BC
  m_dwBoneMatrix = 0x660; // 0x660, 0x894, 0x8A4
  m_dwMaxSpeed = 0x1150; // 0x1150

  m_mdwCurWeapID_Offsets[0] = 0x15D8; // 0x15D8
  m_mdwCurWeapID_Offsets[1] = 0x6C; // 0x6C

  m_mdwCharType_Offsets[0] = 0x24; // 0x24
  m_mdwCharType_Offsets[1] = 0x20; //  0x20
  m_mdwCharType_Offsets[2] = 0x250; // 0x250

  m_mflAngleToTarget[0] = 0.0f;
  m_mflAngleToTarget[1] = 0.0f;
  m_mflAngleToTarget[2] = 0.0f;

  m_mflCurrentBonePos[0] = 0.0f;
  m_mflCurrentBonePos[1] = 0.0f;
  m_mflCurrentBonePos[2] = 0.0f;

	SetIndex(playerIndex);
  SetEntityListStartAddress(entityStartAddress);
  SetEntityStructSize(entityStructSize);

  UpdateBase();
}

C_Player::~C_Player()
{

}

BOOL C_Player::Equals(C_Player* otherPlayer)
{
  if (GetBase() == otherPlayer->GetBase()) return TRUE;
  return FALSE;
}

DWORD C_Player::GetStartAddress()
{
  return m_dwEntityListStartAddress;
}

BOOL C_Player::SetIndex(INT newIndex)
{
  if (newIndex < 0) return FALSE;
  m_iIndex = newIndex;
  return TRUE;
}

INT C_Player::GetIndex()
{
  return m_iIndex;
}

BOOL C_Player::SetEntityListStartAddress(DWORD newEntityListStartAddress)
{
  if (newEntityListStartAddress <= 0) return FALSE;
  m_dwEntityListStartAddress = newEntityListStartAddress;
  return TRUE;
}

BOOL C_Player::SetEntityStructSize(DWORD newEntityStructSize)
{
  if (newEntityStructSize <= 0) return FALSE;
  m_dwEntityStructSize = newEntityStructSize;
  return TRUE;
}

BOOL C_Player::UpdateBase(DWORD newBaseAddress)
{
  if (newBaseAddress <= 0)
  {
    m_dwBase = *(PDWORD)(m_pCManager->m_dwClientDll + m_dwEntityListStartAddress + m_iIndex * m_dwEntityStructSize);
    if (m_dwBase != 0) return TRUE;
    return FALSE;
  }
  m_dwBase = newBaseAddress;
  return TRUE;
}

C_CheatManager* C_Player::CManager()
{
	return m_pCManager;
}

C_EntityManager* C_Player::EManager()
{
	return m_pEManager;
}

PFLOAT C_Player::GetAngle()
{
	return m_mflAngleToTarget;
}

PFLOAT C_Player::CalculateAngleTo(C_Player* target, AngleCalculateTypes calculateType, int bone)
{
  if (target == 0 || !target->IsValid()) return m_mflAngleToTarget;

	PFLOAT thisPos;
	PFLOAT targetPos;

  FLOAT delta[3];

	switch (calculateType)
	{
	case CalculateByHitBox:
		thisPos = this->Position();
		targetPos = target->Position();

    delta[0] = targetPos[0] - thisPos[0];
    delta[1] = targetPos[1] - thisPos[1];
    delta[2] = targetPos[2] - (thisPos[2] + this->YDiff() - Y_DIFFERENCE) + 16.0f; // +22.0f // +16.0f
    if (target->Flag() == FlagDucked) delta[2] -= 18.0f;
		break;
	case CalculateBySkin:
		thisPos = this->BonePos(bone);
    targetPos = target->Position(); //target->BonePos(11);

    delta[0] = targetPos[0] - thisPos[0];
    delta[1] = targetPos[1] - thisPos[1];
    delta[2] = targetPos[2] - thisPos[2] + target->YDiff() + 2.0f;
		break;
  default:
    return m_mflAngleToTarget;
	}

	FLOAT hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
  m_mflAngleToTarget[0] = (FLOAT)(atan(delta[2] / hyp) * 57.2957795131); // 57.2957795131 == (180.0f / M_PI)
  m_mflAngleToTarget[1] = (FLOAT)(atan(delta[1] / delta[0]) * 57.2957795131); // 57.2957795131 == (180.0f / M_PI)
  m_mflAngleToTarget[2] = 0.0f;

	if (delta[0] >= 0.0f && delta[1] < 0.0f) m_mflAngleToTarget[1] += 180.0f;
  else if (delta[0] >= 0.0f && delta[1] >= 0.0f) m_mflAngleToTarget[1] -= 180.0f;

	return m_mflAngleToTarget;
}

FLOAT C_Player::DistanceTo(C_Player* player)
{
	if (player == 0 || !player->IsValid()) return 0.0f;
	return StaticFunctions::Get3dDistance(this->Position(), player->Position());
}

BOOL C_Player::IsValid()
{
  return UpdateBase();
}

DWORD C_Player::GetBase()
{
	return m_dwBase;
}

Flags C_Player::Flag()
{
  if (!IsValid()) return FlagUnknown;
  return (Flags)*(PINT)(m_dwFlag + m_dwBase);
}

Teams C_Player::Team()
{
  switch (CurWeapID())
  {
    case WeaponID_TANK_CLAW:
    case WeaponID_HUNTER_CLAW:
    case WeaponID_BOOMER_CLAW:
    case WeaponID_SMOKER_CLAW: return TeamInfect;
    case WeaponID_SPECTATOR: return TeamSpec;
    case WeaponID_INVALID: return TeamInvalid;
    default: return TeamSurv;
  }
}

BOOL C_Player::SetTeam(Teams newTeamNum)
{
  if (!IsValid()) return FALSE;
  *(PINT)(m_dwTeam + m_dwBase) = (INT)newTeamNum;
  return TRUE;
}

INT C_Player::Health()
{
  if (!IsValid()) return -1;

  return *(PINT)(m_dwHealth + m_dwBase);
}

FLOAT C_Player::JumpVelocity()
{
  if (!IsValid()) return 0.0f;
  return *(PFLOAT)(m_dwJumpVelocity + m_dwBase);
}

FLOAT C_Player::YDiff()
{
  if (!IsValid()) return 0.0f;
  return *(PFLOAT)(m_dwYDiff + m_dwBase);
}

PFLOAT C_Player::Position()
{
  if (!IsValid()) return m_mflCurrentBonePos;
  return (PFLOAT)(m_dwPosition + m_dwBase);
}

BOOL C_Player::IsAlive()
{
  if (!IsValid()) return FALSE;

  if (*(PBYTE)(m_dwLifeStatus + m_dwBase) == (BYTE)0 && Health() > 0) return TRUE;
  return FALSE;
}

BOOL C_Player::IsSpawned()
{
  if (!IsValid()) return FALSE;
  if (*(PINT)(m_dwIsSpawned + m_dwBase) == 1) return TRUE;
	else return FALSE;
}

PFLOAT C_Player::BonePos(INT boneNum)
{
  if (boneNum < 0 || boneNum > 52) return m_mflCurrentBonePos;
  if (!IsValid()) return m_mflCurrentBonePos;

  if (m_dwBase == NULL || m_dwBoneMatrix == NULL) return m_mflCurrentBonePos;

  DWORD Matrix = *(PDWORD)(m_dwBase + m_dwBoneMatrix);
  if (Matrix == NULL) return m_mflCurrentBonePos;

  m_mflCurrentBonePos[0] = *(PFLOAT)(Matrix + boneNum * 0x30 + 0x0C);
  m_mflCurrentBonePos[1] = *(PFLOAT)(Matrix + boneNum * 0x30 + 0x1C);
  m_mflCurrentBonePos[2] = *(PFLOAT)(Matrix + boneNum * 0x30 + 0x2C);

	return m_mflCurrentBonePos;
}

FLOAT C_Player::MaxSpeed()
{
  if (!IsValid()) return 0.0f;
  return *(PFLOAT)(m_dwMaxSpeed + m_dwBase);
}

WeaponIDs C_Player::CurWeapID()
{
  if (!IsValid()) return WeaponID_INVALID;
  return (WeaponIDs)*(PINT)(*(PDWORD)(m_dwBase + m_mdwCurWeapID_Offsets[0]) + m_mdwCurWeapID_Offsets[1]);
}

CharacterTypes C_Player::CharType()
{
  if (!IsValid()) return CharacterType_INVALID;
  return (CharacterTypes)*(PINT)(*(PDWORD)(*(PDWORD)(m_dwBase + m_mdwCharType_Offsets[0]) + m_mdwCharType_Offsets[1]) + m_mdwCharType_Offsets[2]);
}