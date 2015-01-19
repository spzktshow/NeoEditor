//
//  NConfigManager.cpp
//  NeoEditor
//
//  Created by RockLee on 14-12-7.
//
//

#include "NConfigManager.h"
US_NS_N;
/**************ConfigManager*********/
static ConfigManager * configManagerInstance;

ConfigManager * ConfigManager::getInstance()
{
    if (configManagerInstance == nullptr)
    {
        configManagerInstance = new ConfigManager();
    }
    return configManagerInstance;
}

ConfigAble * ConfigManager::getConfigByName(std::string nameValue)
{
    for (ConfigAble * configable : configs) {
        if (configable->getConfigName() == nameValue) return configable;
    }
    return nullptr;
}

void ConfigManager::disposeConfig(std::string configNameValue)
{
    ConfigAble * configAble = this->getConfigByName(configNameValue);
    if (configAble != nullptr);
    {
        configAble->dispose();
    }
    configs.eraseObject(configAble);
}

void ConfigManager::dispose()
{
    for (ConfigAble * configAble : configs) {
        configAble->dispose();
    }
    configs.clear();
}

void ConfigManager::addConfig(neo::ConfigAble *configAbleValue)
{
    ConfigAble * configAble = this->getConfigByName(configAbleValue->getConfigName());
    if (configAble != nullptr) return;
    configs.pushBack(configAbleValue);
}