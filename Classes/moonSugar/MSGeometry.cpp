//
//  MSGeometry.cpp
//  MyPro
//
//  Created by spzktshow on 14-8-28.
//
//

#include "MSGeometry.h"

NS_MS_BEGIN

float Geometry::radiansToAngle(float radians)
{
    return 180 * radians / PI;
}

float Geometry::angleToRadians(float angle)
{
    return PI * angle / 180;
}

NS_MS_END;