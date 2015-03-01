//
//  NState.h
//  NeoEditor
//
//  Created by RockLee on 14-10-31.
//
//

#ifndef __NeoEditor__NState__
#define __NeoEditor__NState__

#include "Neo.h"

NS_N_BEGIN

class StateData : public cocos2d::Node
{
public:
    StateData(std::string stateTypeValue):stateType(stateTypeValue){};
    virtual ~StateData(){};
    
    virtual void start();/****启动状态****/
    virtual void stop();/*****暂停状态****/
    virtual void resume();/****继续状态****/
    virtual void reset();/*****重置状态****/
    
    bool isStateRunning();/****检测状态是否在执行****/
    bool isStateStart();/*******检测状态是否已经启动******/
    bool isStateComplete();/******检测状态是否已经完成******/
    
    std::string getStateType();
    
    static StateData * create(std::string stateTypeValue)
    {
        StateData * stateData = new StateData(stateTypeValue);
        if (stateData && stateData->init())
        {
            stateData->autorelease();
            return stateData;
        }
        CC_SAFE_DELETE(stateData);
        return nullptr;
    };
protected:
    bool stateRunning;
    bool stateStart;
    bool stateComplete;
    
    std::string stateType;
};

class StateOperationData : public StateData
{
public:
    StateOperationData(std::string stateTypeValue, std::string operationTypeValue):StateData(stateTypeValue),operationType(operationTypeValue){};
    virtual ~StateOperationData(){};
    
    std::string getOperationType();
    
    static StateOperationData * create(std::string stateTypeValue, std::string operationTypeValue)
    {
        StateOperationData * stateOperationData = new StateOperationData(stateTypeValue, operationTypeValue);
        if (stateOperationData && stateOperationData->init())
        {
            stateOperationData->autorelease();
            return stateOperationData;
        }
        CC_SAFE_DELETE(stateOperationData);
        return nullptr;
    };
protected:
    std::string operationType;
};

class StateContextAble
{
public:
    StateContextAble(){};
    virtual ~StateContextAble(){};
    
    virtual void insertStateData(StateData *);
    
    virtual void insertStateData(StateData *, unsigned int);/*****在特定的索引下插入状态*****/
    
    virtual void removeStateData(StateData *);/******从列表中移除一个状态******/
};

/*****栈式状态上下文******/
class StackStateContext : public cocos2d::Ref, StateContextAble
{
public:
    StackStateContext(){};
    virtual ~StackStateContext(){};
    
    void popStateData();/*****从列队顶部弹出一个状态*****/
    
    void autoExecute();/******自动执行下一个状态******/
    
    void popStateDataAutoExecute();/*****从顶部弹出状态，然后自动执行下一个状态******/
    
    virtual void insertStateData(StateData *);/****在列队顶部插入状态****/
    
    CREATE_REF_FUNC(StackStateContext);
protected:
    cocos2d::Vector<StateData *> stateStack;
};

/******并行状态上下文******/
class ParallelStateContext : public cocos2d::Ref, StateContextAble
{
public:
    ParallelStateContext(){};
    virtual ~ParallelStateContext(){};
protected:
    cocos2d::Vector<StateData *> parallelList;
};

NS_N_END;

#endif /* defined(__NeoEditor__NState__) */
