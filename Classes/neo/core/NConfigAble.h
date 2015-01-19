//
//  NConfigAble.h
//  NeoEditor
//
//  Created by RockLee on 14-12-21.
//
//

#ifndef __NeoEditor__NConfigAble__
#define __NeoEditor__NConfigAble__

#include "Neo.h"

NS_N_BEGIN

class ConfigAble : public cocos2d::Ref
{
public:
    ConfigAble(std::string configNameValue):hasInit(false){};
    ~ConfigAble(){};
    
    virtual void parse(std::string configData);
    virtual void dispose();
    
    bool checkInited();
    
    std::string getConfigName();
protected:
    bool hasInit;
    std::string configName;
};

NS_N_END;

#endif /* defined(__NeoEditor__NConfigAble__) */
