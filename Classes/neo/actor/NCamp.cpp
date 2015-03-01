//
//  NCamp.cpp
//  NeoEditor
//
//  Created by RockLee on 14-11-11.
//
//

#include "NCamp.h"

US_NS_N;
/***********CampRelationDef***********/
CampRelationDef::CampRelationDef(unsigned int campIdValue, char relationshipValue)
{
    this->campId = campIdValue;
    this->relationship = relationshipValue;
}

CampRelationDef * CampRelationDef::create(unsigned int campIdValue, char relationshipValue)
{
    CampRelationDef * def = new CampRelationDef(campIdValue, relationshipValue);
    if (def)
    {
        def->autorelease();
        return def;
    }
    CC_SAFE_DELETE(def);
    return nullptr;
}

unsigned int CampRelationDef::getCampId()
{
    return campId;
}

char CampRelationDef::getRelationship()
{
    return relationship;
}

/***********Camp************/
CampDef::CampDef(unsigned int campIdValue, cocos2d::Vector<CampRelationDef *> relationValue, std::string nameValue)
{
    campId = campIdValue;
    relation = relationValue;
    name = nameValue;
}

CampDef * CampDef::create(unsigned int campIdValue, cocos2d::Vector<CampRelationDef *> relationValue, std::string nameValue)
{
    CampDef * def = new CampDef(campIdValue, relationValue, nameValue);
    if (def)
    {
        def->autorelease();
        return def;
    }
    CC_SAFE_DELETE(def);
    return nullptr;
}

const cocos2d::Vector<CampRelationDef *> CampDef::getRelation()
{
    return relation;
}

unsigned int CampDef::getCampId()
{
    return campId;
}

CampRelationDef * CampDef::getCampRelationDefByCampId(unsigned int campIdValue)
{
    size_t n = relation.size();
    for (int i = 0; i < n; i++) {
        CampRelationDef * def = relation.at(i);
        if (def->getCampId() == campIdValue) return def;
    }
    return nullptr;
}

std::string CampDef::getName()
{
    return name;
}

/***************CampConfig****************/
const cocos2d::Vector<CampDef *> CampConfig::getCampDefs()
{
    return campDefs;
}

void CampConfig::parse(std::string configData)
{
    rapidjson::Document jsonDict;
    jsonDict.Parse<0>(configData.c_str());
    if (jsonDict.HasParseError())
    {
        cocos2d::log("CampConfig parse error");
    }
    unsigned int n = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(jsonDict, CAMP_CONFIG_TAG_CAMPDEFS);
    for (int i = 0; i < n; i ++)
    {
        const rapidjson::Value& campDefV = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(jsonDict, CAMP_CONFIG_TAG_CAMPDEFS, i);
        unsigned int campId = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(campDefV, CAMP_CONFIG_TAG_CAMP_ID);
        unsigned int m = cocostudio::DictionaryHelper::getInstance()->getArrayCount_json(campDefV, CAMP_CONFIG_TAG_RELATIONSHIPDEFS);
        std::string name = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(campDefV, CAMP_COMFIG_TAG_NAME);
        cocos2d::Vector<CampRelationDef *> campRelationDefs;
        for (int j = 0; j < m; j ++) {
            const rapidjson::Value& campRelationDefV = cocostudio::DictionaryHelper::getInstance()->getDictionaryFromArray_json(campDefV, CAMP_CONFIG_TAG_RELATIONSHIPDEFS, j);
            unsigned int campRelationId = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(campRelationDefV, CAMP_CONFIG_TAG_CAMP_ID);
            char relationship = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(campRelationDefV, CAMP_CONFIG_TAG_RELATIONSHIP);
            CampRelationDef * campRelationDef = CampRelationDef::create(campRelationId, relationship);
            campRelationDefs.pushBack(campRelationDef);
        }
        CampDef * campDef = CampDef::create(campId, campRelationDefs, name);
        campDefs.pushBack(campDef);
    }
    ConfigAble::parse(configData);
}

void CampConfig::dispose()
{
    ConfigAble::dispose();
    campDefs.clear();
}

/*****************CampRelationData****************/
char CampRelationData::getRelationship()
{
    return relationship;
}

void CampRelationData::setRelationship(char relationshipValue)
{
    relationship = relationshipValue;
}

unsigned int CampRelationData::getCampId()
{
    return relationship;
}

void CampRelationData::setCampId(unsigned int campIdValue)
{
    campId = campIdValue;
}

/*******************CampData********************/
int CampData::addCampRelationData(neo::CampRelationData *campReleationDataValue)
{
    int index = checkCampRelationData(campReleationDataValue->getCampId());
    if (index == -1)
    {
        campDatas.pushBack(campReleationDataValue);
    }
    return index;
}

void CampData::removeCampRelationData(unsigned int campIdValue)
{
    int index = checkCampRelationData(campIdValue);
    if (index != -1)
    {
        campDatas.erase(index);
    }
}

void CampData::removeCampRelationData(neo::CampRelationData *campRelationDataValue)
{
    int index = checkCampRelationData(campRelationDataValue->getCampId());
    if (index != -1)
    {
        campDatas.erase(index);
    }
}

CampRelationData * CampData::getCampRelationData(unsigned int campIdValue)
{
    int index = checkCampRelationData(campIdValue);
    if (index != -1)
    {
        return campDatas.at(index);
    }
    return nullptr;
}

int CampData::checkCampRelationData(unsigned int campIdValue)
{
    int index = 0;
    for (auto campRelationData : campDatas)
    {
        if (campRelationData->getCampId() == campIdValue)
        {
            return index;
        }
        index ++;
    }
    return -1;
}

/***********CampUtils*************/
CampRelationData * CampUtils::createCampRelationData(neo::CampRelationDef *campRelationDefValue)
{
    CampRelationData * campRelationData = CampRelationData::create();
    campRelationData->setCampId(campRelationDefValue->getCampId());
    campRelationData->setRelationship(campRelationDefValue->getRelationship());
    return campRelationData;
}

CampData * CampUtils::createCampData(neo::CampDef *campDefValue)
{
    CampData * campData = CampData::create();
    for (auto campRelationDef : campDefValue->getRelation())
    {
        CampRelationData * campRelationData = CampUtils::createCampRelationData(campRelationDef);
        campData->addCampRelationData(campRelationData);
    }
    return campData;
}