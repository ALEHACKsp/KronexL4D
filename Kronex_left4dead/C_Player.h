#pragma once

class C_Player
{
public:
	C_Player(C_EntityMgr* entityManager, int playerIndex, DWORD entityStartAddress, DWORD entityStructSize);
	virtual ~C_Player();

	C_CheatMgr* CManager();
	C_EntityMgr* EManager();

  bool SetEntityListStartAddress(DWORD newEntityListStartAddress);
  bool SetEntityStructSize(DWORD newEntityStructSize);
  bool SetIndex(int newIndex);
  bool UpdateBase(DWORD newBaseAddress = 0);

  int GetIndex();
  DWORD GetStartAddress();
  DWORD GetBase();

  bool IsValid();
  bool Equals(C_Player* otherPlayer);

  ClassIds ClassID();
  int Health();
  int MaxHealth();
  int TickBase();
  bool SetTeam(int newTeamNum);
	bool IsAlive();
	bool IsSpawned();
  bool Incapped();
  float YDiff();
  float JumpVelocity();
  float Velocity(int coordType);
	float MaxSpeed();
  float* Position();
  float* BonePos(int boneNum);
  int Team();
  int Flag();
  int TankFrustration();
  CBaseHandle ActiveWeapon();
  CBaseHandle ObserverTarget();
  CBaseEntity* BaseEntity();
  int CurWeapID();
  int CharType();
  string Nickname();

  float* CalculateAngleTo(C_Player* player, int bone);
  float* GetAngle();
  float DistanceTo(C_Player* player);

  /////////////////////////////////////////////////////////

  C_CheatMgr* pCMgr;
  C_EntityMgr* pEMgr;

  int m_iIndex;

  DWORD dwEntListStartAdr;
  DWORD dwEntStructSize;

  DWORD m_dwBase;
  DWORD dwJumpVelocity;
  DWORD dwTeam;
  DWORD dwHealth;
  DWORD dwMaxHealth;
  DWORD dwFlag;
  DWORD dwYDiff;
  DWORD dwVelocity;
  DWORD dwPosition;
  //DWORD dwCharType;
  DWORD dwLifeStatus;
  DWORD dwIncapped;
  DWORD dwTankFrustration;
  DWORD dwTickBase;
  DWORD dwIsSpawned;
  DWORD dwBoneMatrix;
  DWORD dwMaxSpeed;
  DWORD dwszLastPlaceName;
  DWORD mdwCurWeapID_Offsets[2];
  DWORD mdwCharType_Offsets[2];
  DWORD mdwClassID_Offsets[4];

  float mflAngleToTarget[3];
  float mflCurrentBonePos[3];

  //float flPosScreen_X;
  //float flPosScreen_Y;
  Vector vBonePos[53]; // Number of bone may variety from 0 to 52 include

  DWORD dwActiveWeapon;
  DWORD dwObserverTarget;
};

