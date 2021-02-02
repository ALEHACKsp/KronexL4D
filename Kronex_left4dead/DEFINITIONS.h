#pragma once

typedef void (__thiscall *CreateMoveFn)(IBaseClientDLL* thisptr, int sequence_number, float input_sample_frametime, bool active);
typedef bool (__thiscall *CreateMoveNewFn)(void* thisptr, float flInputSampleTime, CUserCmd *cmd);
typedef void (__thiscall *PaintTraverseFn)(vgui::IPanel* thisptr, unsigned int VGUIPanel, bool forcerepaint, bool allowforce);
typedef void (__thiscall *ProcessMovementFn)(IGameMovement* thisptr, CBasePlayer* pPlayer, CMoveData* pMove);
typedef void (__thiscall *SetupMoveFn)(IPrediction* thisptr, C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move);
typedef void (__thiscall *FinishMoveFn)(IPrediction* thisptr, C_BasePlayer *player, CUserCmd *ucmd, CMoveData *move);
typedef void (__thiscall *TraceRayFn)(IEngineTrace* thisptr, const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);

typedef int(__thiscall *DrawModelFn)(
  IVModelRender* thisptr,
  int flags,
  IClientRenderable *pRenderable,
  ModelInstanceHandle_t instance,
  int entity_index,
  const model_t *model,
  Vector const &origin,
  QAngle const &angles,
  int skin,
  int body,
  int hitboxset,
  const matrix3x4_t *modelToWorld,
  const matrix3x4_t *pLightingOffset);

typedef void(__thiscall *DrawModelExecuteFn)(
  IVModelRender* thisptr,
  const DrawModelState_t &state,
  const ModelRenderInfo_t &pInfo,
  matrix3x4_t *pCustomBoneToWorld);

typedef void (*FnChangeCallback_t)(IConVar *var, const char *pOldValue, float flOldValue);
typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef float	(*SharedRandomFloatFn)(const char *sharedname, float flMinVal, float flMaxVal, int additionalSeed);
typedef float (*SetPredictionRandomSeedFn)(const CUserCmd *cmd);

typedef float (*RandomFloat_t)(float, float);
typedef void (*RandomSeed_t)(unsigned int);

typedef float matrix3x4[3][4];

#define IS_EXEC_ALLOWED (g_pEngineClient->IsConnected() && g_pEngineClient->IsInGame())

#define DEG_TO_RAD(degrees) (degrees * M_PI / 180.0)
#define RAD_TO_DEG(radians) (radians * 180.0 / M_PI)

#define DRAW_BY_HITBOX          0
#define DRAW_BY_BONEMATRIX      1

#define SORT_BY_ANGLE           0
#define SORT_BY_HEALTH          1
#define SORT_BY_DISTANCE        2

#define CH_NOTHING              0
#define CH_AIMBOT               (1 << 0)
#define CH_AUTORESP             (1 << 1)
#define CH_BHOP                 (1 << 2)
#define CH_CEILING              (1 << 3)
#define CH_ESP                  (1 << 4)
#define CH_FAKELAG              (1 << 5)
#define CH_GLOWHACK             (1 << 6)
#define CH_NAMESTEALER          (1 << 7)
#define CH_NORECOIL             (1 << 8)
#define CH_NOSPREAD             (1 << 9)
#define CH_TELEPORTANDCRUSH     (1 << 10)
#define CH_RADAR                (1 << 11)
#define CH_MATHACK              (1 << 12)
#define CH_ALL (CH_MATHACK|CH_GLOWHACK|CH_RADAR|CH_AIMBOT|CH_AUTORESP|CH_BHOP|CH_CEILING|CH_ESP|CH_FAKELAG|CH_NAMESTEALER|CH_NORECOIL|CH_TELEPORTANDCRUSH)

                                          // 32  30  28  26  24  22  20  18  16  14  12  10  8 7 6 5 4 3 2 1 number of bit
#define IN_ATTACK		            (1 << 0)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
#define IN_JUMP			            (1 << 1)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0
#define IN_DUCK			            (1 << 2)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0
#define IN_FORWARD		          (1 << 3)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0
#define IN_BACK			            (1 << 4)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0
#define IN_USE			            (1 << 5)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0
#define IN_CANCEL		            (1 << 6)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
#define IN_LEFT			            (1 << 7)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0
#define IN_RIGHT		            (1 << 8)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0
#define IN_MOVELEFT		          (1 << 9)  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0
#define IN_MOVERIGHT	          (1 << 10) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
#define IN_ATTACK2		          (1 << 11) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
#define IN_RUN			            (1 << 12) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_RELOAD		            (1 << 13) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_ALT1			            (1 << 14) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_ALT2			            (1 << 15) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_SCORE		            (1 << 16) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_SPEED		            (1 << 17) // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_WALK			            (1 << 18) // 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_ZOOM			            (1 << 19) // 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_WEAPON1		          (1 << 20) // 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_WEAPON2		          (1 << 21) // 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
#define IN_BULLRUSH		          (1 << 22) // 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

#define ACTION_MINUS            4
#define ACTION_PLUS             5
#define ACTION_DO               6

#define TEAM_INVALID            -1
#define TEAM_SPEC               1
#define TEAM_SURV               2
#define TEAM_INFECT             3

#define FLAG_UNKNOWN            -1
#define FLAG_ON_STAIRS          128
#define FLAG_ON_LAND            129
#define FLAG_IN_AIR             130
#define FLAG_DUCKED             131

#define WEAPON_ID_INVALID       -1
#define WEAPON_ID_SPECTATOR     0
#define WEAPON_ID_PISTOL        1
#define WEAPON_ID_SMG           2
#define WEAPON_ID_PUMPSHOTGUN   3
#define WEAPON_ID_AUTOSHOTGUN   4
#define WEAPON_ID_RIFLE         5
#define WEAPON_ID_HUNTINGRIFLE  6
#define WEAPON_ID_FIRSTAIDKID   8
#define WEAPON_ID_MOLOTOV       9
#define WEAPON_ID_PIPEBOMB      10
#define WEAPON_ID_PAINPILLS     12
#define WEAPON_ID_GASCAN        14
#define WEAPON_ID_PROPANETANK   15
#define WEAPON_ID_OXYGENTANK    16
#define WEAPON_ID_TANK_CLAW     17
#define WEAPON_ID_HUNTER_CLAW   18
#define WEAPON_ID_BOOMER_CLAW   19
#define WEAPON_ID_SMOKER_CLAW   20

#define CHARACTER_TYPE_INVALID  -1
#define CHARACTER_TYPE_SPEC     -2
#define CHARACTER_TYPE_SURV     -3
#define CHARACTER_TYPE_SMOKER   -4
#define CHARACTER_TYPE_BOOMER   -5
#define CHARACTER_TYPE_HUNTER   -6
#define CHARACTER_TYPE_TANK     -7

enum ValueTypes
{
  UnknownValue,
  IntValue,
  FloatValue,
  StringValue
};

enum ClassIds
{
  ClassID_Unknown = -1,
  ClassID_SurvivorBot = 219,
  ClassID_Hunter = 209,
  ClassID_Smoker = 215,
  ClassID_Boomer = 0,
  ClassID_Tank = 220,
  ClassID_Witch = 221,
  ClassID_Infected = 210,
  ClassID_TerrorWeapon = 183,
  ClassID_TerrorGun = 179,
  ClassID_TankClaw = 136,
  ClassID_SubMachinegun = 132,
  ClassID_SniperRifle = 126,
  ClassID_SmokerClaw = 124,
  ClassID_PumpShotgun = 116,
  ClassID_PropaneTank = 109,
  ClassID_Pistol = 100,
  ClassID_PipeBombProjectile = 99,
  ClassID_PipeBomb = 98,
  ClassID_PainPills = 90,
  ClassID_OxygenTank = 89,
  ClassID_PropMountedGun = 114,
  ClassID_MolotovProjectile = 88,
  ClassID_Molotov = 87,
  ClassID_PropMinigun = 113,
  ClassID_HunterClaw = 80,
  ClassID_GasCan = 78,
  ClassID_FirstAidKit = 58,
  ClassID_Claw = 31,
  ClassID_TEBullets = 155,
  ClassID_BoomerClaw = 27,
  ClassID_BaseShotgun = 18,
  ClassID_AutoShotgun = 2,
  ClassID_AssaultRifle = 1,
  ClassID_NextBotCombatCharacter = 212,
  ClassID_Inferno = 81,
  ClassID_Vomit = 199,
  ClassID_Tongue = 194,
  ClassID_Throw = 193,
  ClassID_Lunge = 85,
  ClassID_BaseAbility = 3,
  ClassID_TutorLesson = 197,
  ClassID_TransitioningPlayer = 195,
  ClassID_TerrorViewModel = 182,
  ClassID_FuncRagdollFader = 71,
  ClassID_TerrorGameRulesProxy = 178,
  ClassID_SurvivorPosition = 134,
  ClassID_PropHealthCabinet = 112,
  ClassID_FinaleTrigger = 55,
  ClassID_ClientPath = 32,
  ClassID_TerrorPlayerResource = 181,
  ClassID_TerrorPlayer = 180,
  ClassID_SurvivorRescue = 135,
  ClassID_WeaponAmmoSpawn = 203,
  ClassID_WeaponSpawn = 206,
  ClassID_PropGlowingObject = 111,
  ClassID_EnvWeaponFire = 53,
  ClassID_WeaponCSBaseGun = 205,
  ClassID_WeaponCSBase = 204,
  ClassID_BaseCSGrenade = 9,
  ClassID_CSGameRulesProxy = 35,
  ClassID_WeaponCubemap = 0,
  ClassID_WeaponCycler = 0,
  ClassID_PlantedC4 = 0,
  ClassID_CSTeam = 38,
  ClassID_CSPlayer = 36,
  ClassID_CSRagdoll = 37,
  ClassID_TEPlayerAnimEvent = 175,
  ClassID_BaseCSGrenadeProjectile = 10,
  ClassID_TestTraceline = 191,
  ClassID_TEWorldDecal = 192,
  ClassID_TESpriteSpray = 189,
  ClassID_TESprite = 188,
  ClassID_TESparks = 187,
  ClassID_TESmoke = 186,
  ClassID_TEShowLine = 185,
  ClassID_TEProjectedDecal = 177,
  ClassID_TEPlayerDecal = 176,
  ClassID_TEPhysicsProp = 174,
  ClassID_TEParticleSystem = 173,
  ClassID_TEMuzzleFlash = 172,
  ClassID_TELargeFunnel = 170,
  ClassID_TEKillPlayerAttachments = 169,
  ClassID_TEImpact = 168,
  ClassID_TEGlowSprite = 167,
  ClassID_TEShatterSurface = 184,
  ClassID_TEFootprintDecal = 164,
  ClassID_TEFizz = 163,
  ClassID_TEExplosion = 162,
  ClassID_TEEnergySplash = 161,
  ClassID_TEEffectDispatch = 160,
  ClassID_TEDynamicLight = 159,
  ClassID_TEDecal = 157,
  ClassID_TEClientProjectile = 156,
  ClassID_TEBubbleTrail = 154,
  ClassID_TEBubbles = 153,
  ClassID_TEBSPDecal = 152,
  ClassID_TEBreakModel = 151,
  ClassID_TEBloodStream = 150,
  ClassID_TEBloodSprite = 149,
  ClassID_TEBeamSpline = 148,
  ClassID_TEBeamRingPoint = 147,
  ClassID_TEBeamRing = 146,
  ClassID_TEBeamPoints = 145,
  ClassID_TEBeamLaser = 144,
  ClassID_TEBeamFollow = 143,
  ClassID_TEBeamEnts = 142,
  ClassID_TEBeamEntPoint = 141,
  ClassID_TEBaseBeam = 140,
  ClassID_TEArmorRicochet = 139,
  ClassID_TEMetalSparks = 171,
  ClassID_SteamJet = 131,
  ClassID_SmokeStack = 125,
  ClassID_DustTrail = 208,
  ClassID_FireTrail = 57,
  ClassID_SporeTrail = 218,
  ClassID_SporeExplosion = 217,
  ClassID_RocketTrail = 214,
  ClassID_SmokeTrail = 216,
  ClassID_PropVehicleDriveable = 115,
  ClassID_ParticleSmokeGrenade = 213,
  ClassID_ParticleFire = 91,
  ClassID_MovieExplosion = 211,
  ClassID_TEGaussExplosion = 166,
  ClassID_EnvQuadraticBeam = 49,
  ClassID_Embers = 41,
  ClassID_nvWind = 54,
  ClassID_Precipitation = 106,
  ClassID_PrecipitationBlocker = 107,
  ClassID_BaseTempEntity = 20,
  ClassID_HandleTest = 79,
  ClassID_TeamplayRoundBasedRulesProxy = 138,
  ClassID_SpriteTrail = 130,
  ClassID_SpriteOriented = 129,
  ClassID_Sprite = 128,
  ClassID_RagdollPropAttached = 119,
  ClassID_RagdollProp = 118,
  ClassID_PredictedViewModel = 108,
  ClassID_PoseController = 104,
  ClassID_GameRulesProxy = 77,
  ClassID_FuncSimpleLadder = 74,
  ClassID_InfoLadderDismount = 82,
  ClassID_FuncLadder = 67,
  ClassID_TEFoundryHelpers = 165,
  ClassID_EnvDetailController = 45,
  ClassID_World = 207,
  ClassID_WaterLODControl = 202,
  ClassID_WaterBullet = 201,
  ClassID_VoteController = 200,
  ClassID_VGuiScreen = 198,
  ClassID_PropJeep = 0,
  ClassID_PropVehicleChoreoGeneric = 0,
  ClassID_FuncPlayerInfectedClip = 70,
  ClassID_TriggerPlayerMovement = 196,
  ClassID_BaseTrigger = 22,
  ClassID_Test_ProxyToggle_Networkable = 190,
  ClassID_BaseTeamObjectiveResource = 19,
  ClassID_Team = 137,
  ClassID_Flare = 0,
  ClassID_Sun = 133,
  ClassID_ParticlePerformanceMonitor = 92,
  ClassID_SpotlightEnd = 127,
  ClassID_SlideshowDisplay = 123,
  ClassID_ShadowControl = 122,
  ClassID_SceneEntity = 121,
  ClassID_RopeKeyframe = 120,
  ClassID_RagdollManager = 117,
  ClassID_PhysBoxMultiplayer = 95,
  ClassID_PropDoorRotatingCheckpoint = 110,
  ClassID_BasePropDoor = 17,
  ClassID_DynamicProp = 40,
  ClassID_PostProcessController = 105,
  ClassID_PointCommentaryNode = 103,
  ClassID_PlayerResource = 102,
  ClassID_Plasma = 101,
  ClassID_PhysMagnet = 97,
  ClassID_PhysicsProp = 96,
  ClassID_Breakable = 28,
  ClassID_PhysBox = 94,
  ClassID_ParticleSystem = 93,
  ClassID_MaterialModifyControl = 86,
  ClassID_LightGlow = 84,
  ClassID_InfoOverlayAccessor = 83,
  ClassID_FuncTrackTrain = 76,
  ClassID_FuncSmokeVolume = 75,
  ClassID_FuncRotating = 73,
  ClassID_FuncReflectiveGlass = 72,
  ClassID_FuncOccluder = 69,
  ClassID_FuncMoveLinear = 68,
  ClassID_FuncMonitor = 0,
  ClassID_Func_LOD = 62,
  ClassID_FuncElevator = 66,
  ClassID_TEDust = 158,
  ClassID_Func_Dust = 61,
  ClassID_FuncConveyor = 65,
  ClassID_FuncBrush = 64,
  ClassID_BreakableSurface = 30,
  ClassID_FuncAreaPortalWindow = 63,
  ClassID_Fish = 59,
  ClassID_EntityFlame = 43,
  ClassID_FireSmoke = 56,
  ClassID_EnvTonemapController = 52,
  ClassID_EnvScreenEffect = 50,
  ClassID_EnvScreenOverlay = 51,
  ClassID_EnvProjectedTexture = 48,
  ClassID_EnvParticleScript = 47,
  ClassID_FogController = 60,
  ClassID_EnvDOFController = 46,
  ClassID_EntityParticleTrail = 44,
  ClassID_EntityDissolve = 42,
  ClassID_DynamicLight = 39,
  ClassID_ColorCorrectionVolume = 34,
  ClassID_ColorCorrection = 33,
  ClassID_BreakableProp = 29,
  ClassID_BeamSpotlight = 25,
  ClassID_BaseButton = 6,
  ClassID_BaseToggle = 21,
  ClassID_BasePlayer = 16,
  ClassID_BaseFlex = 13,
  ClassID_BaseEntity = 12,
  ClassID_BaseDoor = 11,
  ClassID_BaseCombatCharacter = 7,
  ClassID_BaseAnimatingOverlay = 5,
  ClassID_BoneFollower = 26,
  ClassID_BaseAnimating = 4,
  ClassID_AI_BaseNPC = 0,
  ClassID_Beam = 24,
  ClassID_BaseViewModel = 23,
  ClassID_BaseParticleEntity = 15,
  ClassID_BaseGrenade = 14,
  ClassID_BaseCombatWeapon = 8,
};

enum Modules
{
  Client,
  Engine,
  Server,
  VStdLib,
  MaterialSystem,
  VGUIMatSurface,
  VGUI2,
  OverlayRenderer,
};