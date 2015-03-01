//
//  NActorSource.cpp
//  NeoEditor
//
//  Created by RockLee on 14-12-21.
//
//

#include "NActorSource.h"

US_NS_N;
/**********************ActorSourceDef****************/
SourceType ActorSourceDef::getSourceType()
{
    return sourceType;
}

int ActorSourceDef::getSourceId()
{
    return sourceId;
}

/**********************ActorAnimationsSourceDef***************/
const std::vector<std::string> ActorAnimationsSourceDef::getSourceList()
{
    return sourceList;
}

const cocos2d::Vector<ActorAnimationSourceDef *> ActorAnimationsSourceDef::getAnimationSourceDefs()
{
    return animationSourceDefs;
}

/**********************ActorAnimationConfig*****************/
void ActorAnimationConfig::parse(std::string configData)
{
    rapidjson::Document jsonDict;
    jsonDict.Parse<0>(configData.c_str());
    if (jsonDict.HasParseError())
    {
        cocos2d::log("ActorAnimationConfig parse error");
    }
    unsigned int n = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(jsonDict, ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_LIST);
    for (int i = 0; i < n; i ++) {
        const rapidjson::Value& actorAnimationsSourceDefV = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(jsonDict, ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_LIST, i);
        neo::ActorAnimationsSourceDef * def = this->parseActorAnimationsSourceDef(actorAnimationsSourceDefV);
        this->actorAnimationsSourceDefs.pushBack(def);
    }
    
    ConfigAble::parse(configData);
}

void ActorAnimationConfig::dispose()
{
    ConfigAble::dispose();
    
    actorAnimationsSourceDefs.clear();
}

const ActorAnimationsSourceDef * ActorAnimationConfig::getActorAnimationSourceDefBySourceId(int sourceId)
{
    for (ActorAnimationsSourceDef * actorAnimationsSourceDef : actorAnimationsSourceDefs)
    {
        if (actorAnimationsSourceDef->getSourceId() == sourceId) return actorAnimationsSourceDef;
    }
    return nullptr;
}

const cocos2d::Vector<ActorAnimationsSourceDef *> ActorAnimationConfig::getActorAnimationsSourceDefs()
{
    return actorAnimationsSourceDefs;
}

ActorAnimationSourceDef * ActorAnimationConfig::parseActorAnimationSourceDef(const rapidjson::Value &actorAnimationSourceDefValue)
{
    unsigned int frameCount = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(actorAnimationSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_FRAME_COUNT);
    unsigned int animationTag = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(actorAnimationSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_TAG);
    ActorAnimationSourceDef * actorAnimationSourceDef = ActorAnimationSourceDef::create(frameCount, animationTag);
    return actorAnimationSourceDef;
}

ActorAnimationsSourceDef * ActorAnimationConfig::parseActorAnimationsSourceDef(const rapidjson::Value & actorAnimationsSourceDefValue)
{
    int sourceId = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(actorAnimationsSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_SOURCE_ID);
    std::vector<std::string> sourceList;
    int sourceListSize = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(actorAnimationsSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_SOURCE_LIST);
    for (int i = 0; i < sourceListSize; i ++) {
        std::string source = cocostudio::DictionaryHelper::getInstance()->getStringValueFromArray_json(actorAnimationsSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_SOURCE_LIST, i);
        sourceList.push_back(source);
    }
    int actorAnimationsSourceDefsSize = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(actorAnimationsSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_DEFS);
    cocos2d::Vector<ActorAnimationSourceDef *> actorAnimationSourceDefs;
    for (int i = 0; i < actorAnimationsSourceDefsSize; i ++)
    {
        const rapidjson::Value & actorAnimationSourceDefValue = cocostudio::DictionaryHelper::getInstance()->getSubDictionary_json(actorAnimationsSourceDefValue, ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_DEFS, i);
        ActorAnimationSourceDef * actorAnimationSourceDef = ActorAnimationConfig::parseActorAnimationSourceDef(actorAnimationSourceDefValue);
        actorAnimationSourceDefs.pushBack(actorAnimationSourceDef);
    }
    ActorAnimationsSourceDef * actorAnimationsSourceDef = ActorAnimationsSourceDef::create(sourceId, sourceList, actorAnimationSourceDefs);
    return actorAnimationsSourceDef;
}

/****************ActorAnimationsSourceData************/
bool ActorAnimationsSourceData::init()
{
    return true;
}