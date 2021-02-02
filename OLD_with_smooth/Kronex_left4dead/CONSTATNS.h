#pragma once

const FLOAT Y_DIFFERENCE = 62.0f;
enum Actions
{
	ActionMinus = 4,
	ActionPlus = 5,
  DoAction = 6,
};
enum Teams
{
  TeamInvalid = -1,
	TeamSpec = 1,
	TeamSurv = 2,
	TeamInfect = 3,
};
enum Flags
{
  FlagUnknown = -1,
	FlagOnStairs = 128,
	FlagOnLand = 129,
	FlagInAir = 130,
	FlagDucked = 131,
};
enum TargetSortTypes
{
	SortByDistance,
	SortByAngle,
	SortByHealth,
};
enum AngleCalculateTypes
{
	CalculateByHitBox,
	CalculateBySkin,
};
enum WeaponIDs
{
  WeaponID_INVALID = -1,
  WeaponID_SPECTATOR = 0,
  WeaponID_PISTOL = 1,
  WeaponID_SMG = 2,
  WeaponID_PUMPSHOTGUN = 3,
  WeaponID_AUTOSHOTGUN = 4,
  WeaponID_RIFLE = 5,
  WeaponID_HUNTINGRIFLE = 6,
  WeaponID_FIRSTAIDKID = 8,
  WeaponID_MOLOTOV = 9,
  WeaponID_PIPEBOMB = 10,
  WeaponID_PAINPILLS = 12,
  WeaponID_GASCAN = 14,
  WeaponID_PROPANETANK = 15,
  WeaponID_OXYGENTANK = 16,
  WeaponID_TANK_CLAW = 17,
  WeaponID_HUNTER_CLAW = 18,
  WeaponID_BOOMER_CLAW = 19,
  WeaponID_SMOKER_CLAW = 20,
};
enum CharacterTypes
{
  CharacterType_INVALID = -1,
  CharacterType_SMOKER = 1,
  CharacterType_BOOMER = 2,
  CharacterType_HUNTER = 3,
  CharacterType_TANK = 5,
  CharacterType_BILL = 6,
};