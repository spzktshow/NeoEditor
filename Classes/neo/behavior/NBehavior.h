//
//  NBehavior.h
//  NeoEditor
//
//  Created by RockLee on 14-11-8.
//
//

#ifndef __NeoEditor__NBehavior__
#define __NeoEditor__NBehavior__

#include "Neo.h"

NS_N_BEGIN

#define BEHAVIRO_DEBUG              1

class BehaviorEvent
{
public:
    BehaviorEvent(std::string typeValue):type(typeValue){};
    virtual ~BehaviorEvent(){};
    
    std::string getType();
    
    cocos2d::Map<std::string, cocos2d::Ref *> params;
protected:
    std::string type;
};

class BehaviorOperationEvent : public BehaviorEvent
{
public:
    BehaviorOperationEvent(std::string typeValue, std::string operationTypeValue):BehaviorEvent(typeValue), operationType(operationTypeValue){};
    virtual ~BehaviorOperationEvent(){};
    
    std::string getOperationType();
    
    static BehaviorOperationEvent * create(std::string typeValue, std::string operationTypeValue);
protected:
    std::string operationType;
};

/***************状态机行为抽象函数执行****************/
class BehaviorExecute : public cocos2d::Ref
{
public:
    BehaviorExecute(){};
    ~BehaviorExecute(){};
    
    virtual bool execute(BehaviorEvent *);
    
    CREATE_REF_FUNC(BehaviorExecute);
};

/***===============行为树=================***/
enum BehaviorTreeNode
{
    COMPOSITE = 0,/*****抽象组合节点****/
    SEQUENCE,/******顺序节点*****/
    SELECTOR,/******选择节点*****/
    PARALLEL,/******并行节点*****/
    CONDITION,/******条件节点*****/
    ACTION,/*****抽象动作节点****/
    DECORATOR/******抽象装饰节点*****/
};

/****抽象行为节点****/
class BehaviorNode : public cocos2d::Ref
{
public:
    BehaviorNode(char typeValue){type = typeValue;};
    ~BehaviorNode(){};
    
    virtual bool execute(BehaviorEvent *);
    
#if BEHAVIRO_DEBUG
    std::string nodeName;
#endif
protected:
    char type;
};

/*******抽象组合节点**********/
class CompositeBehaviorNode : public BehaviorNode
{
public:
    CompositeBehaviorNode(char typeValue, cocos2d::Vector<BehaviorNode *> childrenValue);
    ~CompositeBehaviorNode(){};
    
    virtual bool execute(BehaviorEvent *);
protected:
    cocos2d::Vector<BehaviorNode *> children;
};

/*********顺序节点***********/
class SequenceBehaviorNode : public CompositeBehaviorNode
{
public:
    SequenceBehaviorNode(cocos2d::Vector<BehaviorNode *> childrenValue):CompositeBehaviorNode(BehaviorTreeNode::SEQUENCE, childrenValue){};
    ~SequenceBehaviorNode(){};
    
    virtual bool execute(BehaviorEvent *);
    
    static SequenceBehaviorNode * create(cocos2d::Vector<BehaviorNode *> childrenValue)
    {
        SequenceBehaviorNode * behaviorNode = new SequenceBehaviorNode(childrenValue);
        if (behaviorNode)
        {
            behaviorNode->autorelease();
            return behaviorNode;
        }
        CC_SAFE_DELETE(behaviorNode);
        return nullptr;
    }
};

/**********选择节点***********/
class SelectorBehaviorNode : public CompositeBehaviorNode
{
public:
    SelectorBehaviorNode(cocos2d::Vector<BehaviorNode *> childrenValue):CompositeBehaviorNode(BehaviorTreeNode::SELECTOR, childrenValue){};
    ~SelectorBehaviorNode(){};
    
    virtual bool execute(BehaviorEvent *);
    
    static SelectorBehaviorNode * create(cocos2d::Vector<BehaviorNode *> childrenValue)
    {
        SelectorBehaviorNode * behaviorNode = new SelectorBehaviorNode(childrenValue);
        if (behaviorNode)
        {
            behaviorNode->autorelease();
            return behaviorNode;
        }
        CC_SAFE_DELETE(behaviorNode);
        return nullptr;
    }
};

/**********并行节点**********/
class ParallelBehaviorNode : public CompositeBehaviorNode
{
public:
    ParallelBehaviorNode(cocos2d::Vector<BehaviorNode *> childrenValue):CompositeBehaviorNode(BehaviorTreeNode::PARALLEL, childrenValue){};
    ~ParallelBehaviorNode(){};
    
    virtual bool execute(BehaviorEvent *);
    
    static ParallelBehaviorNode * create(cocos2d::Vector<BehaviorNode *> childrenValue)
    {
        ParallelBehaviorNode * behaviorNode = new ParallelBehaviorNode(childrenValue);
        if (behaviorNode)
        {
            behaviorNode->autorelease();
            return behaviorNode;
        }
        CC_SAFE_DELETE(behaviorNode);
        return nullptr;
    }
};

/***********条件节点*********/
class ConditionBehaviorNode : public BehaviorNode
{
public:
    ConditionBehaviorNode(std::string conditionTypeValue):BehaviorNode(BehaviorTreeNode::CONDITION){conditionType = conditionTypeValue;};
    ~ConditionBehaviorNode(){};
    
    std::string getConditionType();
    
    virtual bool execute(BehaviorEvent *);
protected:
    std::string conditionType;
};

/*************装饰节点*********/
class DecoratorBehaviorNode : public BehaviorNode
{
public:
    DecoratorBehaviorNode(std::string decoratorTypeValue, BehaviorNode * childValue);
    ~DecoratorBehaviorNode(){};
    
    std::string getDecoratorType();
    
    virtual bool execute(BehaviorEvent *);
protected:
    std::string decoratorType;
    
    BehaviorNode * child;
};

/*************campareEventType ConditionBehaviorNode*****/
#define CONDITION_CAMPARE_EVENT_TYPE                "campareEventType"
class ConditionBehaviorNodeCampareEventType : public ConditionBehaviorNode
{
public:
    ConditionBehaviorNodeCampareEventType(std::string campareEventTypeValue):ConditionBehaviorNode(CONDITION_CAMPARE_EVENT_TYPE){
        campareEventType = campareEventTypeValue;
    };
    ~ConditionBehaviorNodeCampareEventType(){};
    
    virtual bool execute(BehaviorEvent *);
    
    static ConditionBehaviorNodeCampareEventType * create(std::string campareEventTypeValue)
    {
        ConditionBehaviorNodeCampareEventType * behaviorNode = new ConditionBehaviorNodeCampareEventType(campareEventTypeValue);
        if (behaviorNode)
        {
            behaviorNode->autorelease();
            return behaviorNode;
        }
        CC_SAFE_DELETE(behaviorNode);
        return nullptr;
    }
protected:
    std::string campareEventType;
};

/*************turn DecoratorBehaviorNode**********/
#define DECORATOR_TURN                          "turn"
class DecoratorBehaviorNodeTurn : public DecoratorBehaviorNode
{
public:
    DecoratorBehaviorNodeTurn(BehaviorNode * childValue):DecoratorBehaviorNode(DECORATOR_TURN, childValue){};
    ~DecoratorBehaviorNodeTurn(){};
    
    virtual bool execute(BehaviorEvent *);
    
    static DecoratorBehaviorNodeTurn * create(BehaviorNode * childValue)
    {
        DecoratorBehaviorNodeTurn * behaviorNode = new DecoratorBehaviorNodeTurn(childValue);
        if (behaviorNode)
        {
            behaviorNode->autorelease();
            return behaviorNode;
        }
        CC_SAFE_DELETE(behaviorNode);
        return nullptr;
    }
};

NS_N_END;

#endif /* defined(__NeoEditor__NBehavior__) */
