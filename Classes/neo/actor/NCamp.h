//
//  NCamp.h
//  NeoEditor
//
//  Created by RockLee on 14-11-11.
//
//

#ifndef __NeoEditor__NCamp__
#define __NeoEditor__NCamp__

#include "Neo.h"
#include "cocostudio/DictionaryHelper.h"
#include "NConfigAble.h"

NS_N_BEGIN
class CampRelationDef : public cocos2d::Ref
{
public:
    CampRelationDef(unsigned int campIdValue, char relationshipValue);
    ~CampRelationDef(){};
    
    unsigned int getCampId();
    char getRelationship();
    
    static CampRelationDef * create(unsigned int campIdValue, char relationshipValue);
protected:
    unsigned int campId;
    char relationship;
};

class CampDef : public cocos2d::Ref
{
public:
    CampDef(unsigned int campIdValue, cocos2d::Vector<CampRelationDef *> relationValue, std::string nameValue);
    ~CampDef(){};
    
    unsigned int getCampId();
    
    std::string getName();
    
    CampRelationDef * getCampRelationDefByCampId(unsigned int campIdValue);
    
    const cocos2d::Vector<CampRelationDef *> getRelation();
    
    static CampDef * create(unsigned int campIdValue, cocos2d::Vector<CampRelationDef *> relationValue, std::string nameValue);
protected:
    unsigned int campId;
    
    std::string name;
    
    cocos2d::Vector<CampRelationDef *> relation;
};

#define CAMP_CONFIG_TAG_CAMPDEFS                "campDefs"
#define CAMP_CONFIG_TAG_RELATIONSHIPDEFS        "campRelationDefs"
#define CAMP_CONFIG_TAG_CAMP_ID                 "campId"
#define CAMP_COMFIG_TAG_NAME                    "name"
#define CAMP_CONFIG_TAG_RELATIONSHIP            "relationship"

#define CAMP_CONFIG_NAME                    "camp"
class CampConfig : public ConfigAble
{
public:
    CampConfig():ConfigAble(CAMP_CONFIG_NAME){};
    ~CampConfig(){};
    
    const cocos2d::Vector<CampDef *> getCampDefs();
    
    const CampDef * getCampDefByCampId(unsigned int campIdValue);
    
    virtual void parse(std::string configData);
    virtual void dispose();
    
    CREATE_REF_FUNC(CampConfig);
protected:
    cocos2d::Vector<CampDef *> campDefs;
};

class CampRelationData : public cocos2d::Ref
{
public:
    CampRelationData(){};
    ~CampRelationData(){};
    
    void setCampId(unsigned int campIdValue);
    unsigned int getCampId();
    
    void setRelationship(char relationshipValue);
    char getRelationship();
    
    CREATE_REF_FUNC(CampRelationData);
protected:
    unsigned int campId;
    char relationship;
};

class CampData : public cocos2d::Ref
{
public:
    CampData(){};
    ~CampData(){};
    
    int addCampRelationData(CampRelationData * campReleationDataValue);
    void removeCampRelationData(unsigned int campIdValue);
    void removeCampRelationData(CampRelationData * campRelationDataValue);
    CampRelationData * getCampRelationData(unsigned int campIdValue);
    
    CREATE_REF_FUNC(CampData);
protected:
    unsigned int campId;
    cocos2d::Vector<CampRelationData *> campDatas;
    
    int checkCampRelationData(unsigned int campIdValue);
};

class CampUtils : public cocos2d::Ref
{
public:
    static CampRelationData * createCampRelationData(CampRelationDef * campRelationDefValue);
    static CampData * createCampData(CampDef * campDefValue);
};

NS_N_END;

#endif /* defined(__NeoEditor__NCamp__) */
