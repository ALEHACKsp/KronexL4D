#include <math.h>

#include "StaticFunctions.h"

const FLOAT StaticFunctions::Get2dDistance(PFLOAT point1, PFLOAT point2)
{
	return (FLOAT)sqrt(pow(DOUBLE(point2[0] - point1[0]), 2.0f) +
						         pow(DOUBLE(point2[1] - point1[1]), 2.0f));
}

const FLOAT StaticFunctions::Get3dDistance(PFLOAT point1, PFLOAT point2)
{
	return (FLOAT)sqrt(pow(DOUBLE(point2[0] - point1[0]), 2.0f) +
						         pow(DOUBLE(point2[1] - point1[1]), 2.0f) +
						         pow(DOUBLE(point2[2] - point1[2]), 2.0f));
}


const FLOAT StaticFunctions::GetAngleDistance(PFLOAT angle1, PFLOAT angle2)
{
  FLOAT angleToTarget = StaticFunctions::Get3dDistance(angle1, angle2);
  if (angleToTarget >= 180.0f) angleToTarget = 360.0f - angleToTarget;

  return angleToTarget;
}