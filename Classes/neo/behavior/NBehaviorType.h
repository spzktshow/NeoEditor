//
//  NBehaviorType.h
//  NeoEditor
//
//  Created by RockLee on 15-1-31.
//
//

#ifndef __NeoEditor__NBehaviorType__
#define __NeoEditor__NBehaviorType__

#include "Neo.h"

NS_N_BEGIN

/***===============行为树=================***/
/*****抽象组合节点****/
#define BehaviorTreeNode_composite              "composite"
/******顺序节点*****/
#define BehaviorTreeNode_sequence               "sequence"
/******选择节点*****/
#define BehaviorTreeNode_selector               "selector"
/******并行节点*****/
#define BehaviorTreeNode_parallel               "parallel"
/******条件节点*****/
#define BehaviorTreeNode_condition              "condition"
/*****抽象动作节点****/
#define BehaviorTreeNode_action                 "action"
/******抽象装饰节点*****/
#define BehaviorTreeNode_decorator              "decorator"

NS_N_END;

#endif /* defined(__NeoEditor__NBehaviorType__) */
