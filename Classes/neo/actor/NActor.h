//
//  NActor.h
//  NeoEditor
//
//  Created by RockLee on 14-11-11.
//
//

#ifndef __NeoEditor__NActor__
#define __NeoEditor__NActor__

#include "Neo.h"
#include "NCamp.h"
#include "NActorSource.h"

NS_N_BEGIN
class ActorDef : public cocos2d::Ref
{
public:
    ActorDef():sourceDef(nullptr){};
    ~ActorDef(){
        sourceDef = nullptr;
    };
    /***id***/
    unsigned int actorId;
    std::string name;
    
    /****source*****/
    const ActorSourceDef * sourceDef;
    
    CREATE_REF_FUNC(ActorDef);
};


class ActorData : public cocos2d::Ref
{
public:
    ActorData(ActorDef * actorDefValue):actorDef(actorDefValue), actorSourceData(nullptr), campData(nullptr){};
    ~ActorData(){
        actorDef = nullptr;
        
        if (actorSourceData != nullptr)
        {
            actorSourceData->release();
            actorSourceData = nullptr;
        }
        
        if (campData != nullptr)
        {
            campData->release();
            campData = nullptr;
        }
    };
    
    const ActorDef * actorDef;
    
    void setActorSourceData(ActorSourceData * data)
    {
        if (actorSourceData)
        {
            actorSourceData->release();
        }
        actorSourceData = data;
        if (!actorSourceData) return;
        actorSourceData->retain();
    };
    
    ActorSourceData * getActorSourceData()
    {
        return actorSourceData;
    };
    
    void setCampData(CampData * campDataValue)
    {
        if (campData)
        {
            campData->release();
        }
        campData = campDataValue;
        if (!campData) return;
        campData->retain();
    };
    
    CampData * getCampData()
    {
        return campData;
    };
protected:
    ActorSourceData * actorSourceData;
    CampData * campData;
};

NS_N_END;

#endif /* defined(__NeoEditor__NActor__) */
