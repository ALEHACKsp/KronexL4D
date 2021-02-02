#pragma once

class C_CheatManager;

#include <Windows.h>
#include "C_CheatManager.h"
#include "StaticFunctions.h"

class C_Player
{
public:
	C_Player(C_EntityManager* entityManager, int playerIndex, DWORD entityStartAddress, DWORD entityStructSize);
	virtual ~C_Player();

	C_CheatManager* CManager();
	C_EntityManager* EManager();

  BOOL SetEntityListStartAddress(DWORD newEntityListStartAddress);
  BOOL SetEntityStructSize(DWORD newEntityStructSize);
  BOOL SetIndex(INT newIndex);
  BOOL UpdateBase(DWORD newBaseAddress = 0);

  INT GetIndex();
  DWORD GetStartAddress();
  DWORD GetBase();

  BOOL IsValid();
  BOOL Equals(C_Player* otherPlayer);

  INT Health();
  BOOL SetTeam(Teams newTeamNum);
	BOOL IsAlive();
	BOOL IsSpawned();
  FLOAT YDiff();
  FLOAT JumpVelocity();
	FLOAT MaxSpeed();
  PFLOAT Position();
  PFLOAT BonePos(INT boneNum);
  Teams Team();
  Flags Flag();
  WeaponIDs CurWeapID();
  CharacterTypes CharType();

  PFLOAT CalculateAngleTo(C_Player* player, AngleCalculateTypes calculateType, int bone);
  PFLOAT GetAngle();
  FLOAT DistanceTo(C_Player* player);

private:
  C_CheatManager* m_pCManager;
  C_EntityManager* m_pEManager;

  INT m_iIndex;

  DWORD m_dwEntityListStartAddress;
  DWORD m_dwEntityStructSize;

  DWORD m_dwBase;
  DWORD m_dwJumpVelocity;
  DWORD m_dwTeam;
  DWORD m_dwHealth;
  DWORD m_dwFlag;
  DWORD m_dwYDiff;
  DWORD m_dwPosition;
  DWORD m_dwLifeStatus;
  DWORD m_dwIsSpawned;
  DWORD m_dwBoneMatrix;
  DWORD m_dwMaxSpeed;
  DWORD m_mdwCurWeapID_Offsets[2];
  DWORD m_mdwCharType_Offsets[3];

  FLOAT m_mflAngleToTarget[3];
  FLOAT m_mflCurrentBonePos[3];
};

