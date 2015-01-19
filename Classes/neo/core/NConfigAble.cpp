//
//  NConfigAble.cpp
//  NeoEditor
//
//  Created by RockLee on 14-12-21.
//
//

#include "NConfigAble.h"

US_NS_N;
/**********ConfigAble***********/
void ConfigAble::parse(std::string configData)
{
    this->hasInit = true;
}

void ConfigAble::dispose()
{
    this->hasInit = false;
}

bool ConfigAble::checkInited()
{
    return hasInit;
}

std::string ConfigAble::getConfigName()
{
    return configName;
}