#pragma once

#include <Windows.h>

namespace StaticFunctions
{
  const FLOAT Get2dDistance(PFLOAT point1, PFLOAT point2);
  const FLOAT Get3dDistance(PFLOAT point1, PFLOAT point2);
  const FLOAT GetAngleDistance(PFLOAT angle1, PFLOAT angle2);
};

