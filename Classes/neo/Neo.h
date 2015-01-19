//
//  Neo.h
//  NeoEditor
//
//  Created by RockLee on 14-10-31.
//
//

#ifndef NeoEditor_Neo_h
#define NeoEditor_Neo_h

#include "cocos2d.h"

#define NS_N_BEGIN          namespace neo{
#define NS_N_END            }
#define US_NS_N             using namespace neo

#define CREATE_REF_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#endif
