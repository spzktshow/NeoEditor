//
//  NActorSource.h
//  NeoEditor
//
//  Created by RockLee on 14-12-21.
//
//

#ifndef __NeoEditor__NActorSource__
#define __NeoEditor__NActorSource__

#include "Neo.h"
#include "cocostudio/DictionaryHelper.h"
#include "NConfigAble.h"

NS_N_BEGIN

enum class SourceType
{
    ARMATURE = 0,
    ANIMATIONS,
};

class ActorSourceDef : public cocos2d::Ref
{
public:
    ActorSourceDef(int sourceIdValue, SourceType sourceTypeValue):sourceType(sourceTypeValue), sourceId(sourceIdValue){};
    ~ActorSourceDef(){};
    
    SourceType getSourceType();
    int getSourceId();
protected:
    SourceType sourceType;
    int sourceId;
};

class ActorSourceData : public cocos2d::Ref
{
public:
    ActorSourceData(ActorSourceDef * def):actorSourceDef(def){};
    virtual ~ActorSourceData(){
        actorSourceDef = nullptr;
    };
    
    virtual bool init(){return true;};
    
    const ActorSourceDef * actorSourceDef;
};

class ActorArmatureSourceDef : public ActorSourceDef
{
public:
    ActorArmatureSourceDef(int sourceIdValue):ActorSourceDef(sourceIdValue, SourceType::ARMATURE){};
    ~ActorArmatureSourceDef(){};
    
    static ActorArmatureSourceDef * create(int sourceIdValue)
    {
        ActorArmatureSourceDef * def = new ActorArmatureSourceDef(sourceIdValue);
        if (def)
        {
            def->autorelease();
            return def;
        }
        CC_SAFE_DELETE(def);
        return nullptr;
    };
};

class ActorAnimationSourceDef : public cocos2d::Ref
{
public:
    ActorAnimationSourceDef(unsigned int frameCountValue, unsigned int animationTagValue):frameCount(frameCountValue)
    , animationTag(animationTagValue)
    {};
    ~ActorAnimationSourceDef(){};
    
    unsigned int getFrameCount();
    unsigned int getAnimationTag();
    
    static ActorAnimationSourceDef * create(unsigned int frameCountValue, unsigned int animationTagValue)
    {
        ActorAnimationSourceDef * def = new ActorAnimationSourceDef(frameCountValue, animationTagValue);
        if (def)
        {
            def->autorelease();
            return def;
        }
        CC_SAFE_DELETE(def);
        return nullptr;
    }
protected:
    unsigned int frameCount;
    unsigned int animationTag;
};

class ActorAnimationsSourceDef : public ActorSourceDef
{
public:
    ActorAnimationsSourceDef(int sourceIdValue, std::vector<std::string> sourceListValue, cocos2d::Vector<ActorAnimationSourceDef *> animationsSourceDefsValue):ActorSourceDef(sourceIdValue, SourceType::ANIMATIONS)
    , sourceList(sourceListValue)
    , animationSourceDefs(animationsSourceDefsValue)
    {};
    ~ActorAnimationsSourceDef(){};
    
    const std::vector<std::string> getSourceList();
    
    const cocos2d::Vector<ActorAnimationSourceDef *> getAnimationSourceDefs();
    
    static ActorAnimationsSourceDef * create(int sourceIdValue, std::vector<std::string> sourceListValue, cocos2d::Vector<ActorAnimationSourceDef *> animationsSourceDefsValue)
    {
        ActorAnimationsSourceDef * def = new ActorAnimationsSourceDef(sourceIdValue, sourceListValue, animationsSourceDefsValue);
        if (def)
        {
            def->autorelease();
            return def;
        }
        CC_SAFE_DELETE(def);
        return nullptr;
    };
    
protected:
    cocos2d::Vector<ActorAnimationSourceDef *> animationSourceDefs;
    
    /******plist list******/
    std::vector<std::string> sourceList;
};

#define ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_LIST    "animationSourceList"
#define ACTOR_ANIMATION_CONFIG_TAG_SOURCE_ID            "sourceId"
#define ACTOR_ANIMATION_CONFIG_TAG_FRAME_COUNT          "frameCount"
#define ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_TAG        "animationTag"
#define ACTOR_ANIMATION_CONFIG_TAG_SOURCE_LIST          "sourceList"
#define ACTOR_ANIMATION_CONFIG_TAG_ANIMATION_SOURCE_DEFS    "animationSourceDefs"

#define ACTOR_ANIMATION_CONFIG_NAME                 "actorAnimationConfigName"
class ActorAnimationConfig : public ConfigAble
{
public:
    ActorAnimationConfig():ConfigAble(ACTOR_ANIMATION_CONFIG_NAME){};
    ~ActorAnimationConfig(){};
    
    virtual void parse(std::string configData);
    virtual void dispose();
    
    const ActorAnimationsSourceDef * getActorAnimationSourceDefBySourceId(int sourceId);
    
    const cocos2d::Vector<ActorAnimationsSourceDef *> getActorAnimationsSourceDefs();
    
    CREATE_REF_FUNC(ActorAnimationConfig);
protected:
    cocos2d::Vector<ActorAnimationsSourceDef *> actorAnimationsSourceDefs;
    
    ActorAnimationSourceDef * parseActorAnimationSourceDef(const rapidjson::Value & actorAnimationSourceDefValue);
    ActorAnimationsSourceDef * parseActorAnimationsSourceDef(const rapidjson::Value & actorAnimationsSourceDefValue);
};

class ActorAnimationsSourceData : public ActorSourceData
{
public:
    ActorAnimationsSourceData(ActorAnimationsSourceDef * def):ActorSourceData(def){};
    ~ActorAnimationsSourceData(){};
    
    virtual bool init();
    
    cocos2d::Map<std::string, cocos2d::Animate *> animationDic;
    
    ActorAnimationsSourceDef * getActorAnimationsSourceDef();
    
    const ActorAnimationsSourceDef * aa;
    
    static ActorAnimationsSourceData * create(ActorAnimationsSourceDef * def)
    {
        ActorAnimationsSourceData * data = new ActorAnimationsSourceData(def);
        if (data)
        {
            data->autorelease();
            return data;
        }
        CC_SAFE_DELETE(data);
        return nullptr;
    };
};

NS_N_END;
#endif /* defined(__NeoEditor__NActorSource__) */
