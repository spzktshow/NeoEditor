//
//  NConfigManager.h
//  NeoEditor
//
//  Created by RockLee on 14-12-7.
//
//

#ifndef __NeoEditor__NConfigManager__
#define __NeoEditor__NConfigManager__

#include "NConfigAble.h"

NS_N_BEGIN

class ConfigManager : public cocos2d::Ref
{
public:
    static ConfigManager * getInstance();
    
    ConfigAble * getConfigByName(std::string nameValue);
    
    void disposeConfig(std::string configNameValue);
    void dispose();
    
    void addConfig(ConfigAble * configAbleValue);
protected:
    cocos2d::Vector<ConfigAble *> configs;
};

NS_N_END;

#endif /* defined(__NeoEditor__NConfigManager__) */
