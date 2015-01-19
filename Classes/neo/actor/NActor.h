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
    ActorDef():sourceDef(nullptr), campDef(nullptr){};
    ~ActorDef(){
        sourceDef = nullptr;
        campDef = nullptr;
    };
    /***id***/
    unsigned int actorId;
    std::string name;
    
    /****source*****/
    const ActorSourceDef * sourceDef;
    
    /****camp******/
    const CampDef * campDef;
    
    CREATE_REF_FUNC(ActorDef);
};


class ActorData : public cocos2d::Ref
{
public:
    ActorData(ActorDef * actorDefValue):actorDef(actorDefValue), actorSourceData(nullptr){};
    ~ActorData(){
        actorDef = nullptr;
        
        if (actorSourceData != nullptr)
        {
            actorSourceData->release();
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
    
    const ActorSourceData * getActorSourceData()
    {
        return actorSourceData;
    };
protected:
    ActorSourceData * actorSourceData;
};

NS_N_END;

#endif /* defined(__NeoEditor__NActor__) */
