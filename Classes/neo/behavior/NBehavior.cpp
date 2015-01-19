//
//  NBehavior.cpp
//  NeoEditor
//
//  Created by RockLee on 14-11-8.
//
//

#include "NBehavior.h"

US_NS_N;
/**************BehaviorEvent***********/
std::string BehaviorEvent::getType()
{
    return type;
}
/**************BehaviorExecute*********/
bool BehaviorExecute::execute(neo::BehaviorEvent * behaviorEventValue)
{
    return false;
}

/**************BehaviorNode***********/
bool BehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    return false;
}

/**************CompositeBehaviorNode***********/
bool CompositeBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    return false;
}

CompositeBehaviorNode::CompositeBehaviorNode(char typeValue, cocos2d::Vector<BehaviorNode *> childrenValue):BehaviorNode(typeValue)
{
    children = childrenValue;
}
/****************SequenceBehaviorNode***********/
bool SequenceBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    size_t n = children.size();
    for (int i = 0; i < n; i ++) {
        if (!children.at(i)->execute(behaviorEventValue))
        {
            return false;
        }
    }
    return true;
}

/**********SelectorBehaviorNode**************/
bool SelectorBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    size_t n = children.size();
    for (int i = 0; i < n; i ++) {
        if (children.at(i)->execute(behaviorEventValue))
        {
            return true;
        }
    }
    return false;
}

/************ParallelBehaviorNode**********/
bool ParallelBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    size_t n = children.size();
    for (int i = 0; i < n; i ++) {
        children.at(i)->execute(behaviorEventValue);
    }
    return true;
}

/***********ConditionBehaviorNode***********/
std::string ConditionBehaviorNode::getConditionType()
{
    return conditionType;
}

bool ConditionBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    return false;
}

/************DecoratorBehaviorNode***********/
DecoratorBehaviorNode::DecoratorBehaviorNode(std::string decoratorTypeValue, BehaviorNode * childValue):BehaviorNode(BehaviorTreeNode::DECORATOR)
{
    decoratorType = decoratorTypeValue;
    child = childValue;
}

std::string DecoratorBehaviorNode::getDecoratorType()
{
    return decoratorType;
}

bool DecoratorBehaviorNode::execute(neo::BehaviorEvent * behaviorEventValue)
{
    return false;
}

/******************ConditionBehaviorNode************/
bool ConditionBehaviorNodeCampareEventType::execute(neo::BehaviorEvent * behaviorEventValue)
{
    if (behaviorEventValue->getType() == campareEventType)
    {
        return true;
    }
    return false;
}

/***************DecoratorBehaviorNodeTurn*********/
bool DecoratorBehaviorNodeTurn::execute(neo::BehaviorEvent * behaviorEventValue)
{
    if (child->execute(behaviorEventValue)) return false;
    return true;
}
