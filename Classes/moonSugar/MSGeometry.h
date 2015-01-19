//
//  MSGeometry.h
//  MyPro
//
//  Created by spzktshow on 14-8-28.
//
//

#ifndef __MyPro__MSGeometry__
#define __MyPro__MSGeometry__

#include "moonSugar.h"

NS_MS_BEGIN

#define PI          3.14f

class Geometry : public cocos2d::Ref
{
public:
    /****弧度转角度***/
    static float radiansToAngle(float radians);
    /****角度转弧度***/
    static float angleToRadians(float angle);
};

NS_MS_END;

#endif /* defined(__MyPro__MSGeometry__) */
