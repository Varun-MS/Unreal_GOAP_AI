// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionPlanner.h"
#include "WorldState_Internal.h"
#include <algorithm>
#include "Engine.h"

// Sets default values for this component's properties
UActionPlanner::UActionPlanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionPlanner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

std::vector<NodeRecord>::iterator UActionPlanner::IsContainedInOpenList(WorldState_Internal i_worldState)
{
	return std::find_if(begin(m_openList), end(m_openList), [&](const NodeRecord& n) { return (n.worldState == i_worldState); });
}

bool UActionPlanner::IsContainedInClosedList(WorldState_Internal i_worldState)
{
	if (std::find_if(begin(m_closedList), end(m_closedList), [&](const NodeRecord& n) { return (n.worldState == i_worldState); }) == end(m_closedList))
	{
		return false;
	}

	return true;
}

void UActionPlanner::AddToOpenList(NodeRecord&& i_nodeRecord)
{
	auto it = std::lower_bound(begin(m_openList), end(m_openList), i_nodeRecord);
	m_openList.emplace(it, std::move(i_nodeRecord));
}

//Not responsible to check if the open list is empty!
NodeRecord UActionPlanner::PopAndClose()
{
	m_closedList.push_back(std::move(m_openList.front()));
	m_openList.erase(m_openList.begin());

	return m_closedList.back();
}

int UActionPlanner::CalculateHeuristic(WorldState_Internal i_currentState, WorldState_Internal i_targetState)
{
	return i_currentState.DistanceTo(i_targetState);
}

// Called every frame
void UActionPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<UActionTest*> UActionPlanner::Plan(UWorldState* i_pCurrentState, UWorldState* i_pTargetState, const TArray<UActionTest*>& actions)
{
	if (!i_pCurrentState || !i_pTargetState)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, "Your World States were invalid!");
		return TArray<UActionTest*>();
	}

	WorldState_Internal currentState(i_pCurrentState);
	WorldState_Internal targetState(i_pTargetState);

	if (currentState == targetState)
	{
		return TArray<UActionTest*>();
	}

	// Feasible we'd re-use a planner, so clear out the prior results
	m_openList.clear();
	m_closedList.clear();

	NodeRecord startNode(i_pCurrentState, nullptr, 0, CalculateHeuristic(i_pCurrentState, i_pTargetState), 0);

	m_openList.push_back(std::move(startNode));

	//int iters = 0;
	while (m_openList.size() > 0) {
		//++iters;
		//std::cout << "\n-----------------------\n";
		//std::cout << "Iteration " << iters << std::endl;

		// Look for Node with the lowest-F-score on the open list. Switch it to closed,
		// and hang onto it -- this is our latest node.
		NodeRecord current(PopAndClose());
		//UWorldState* debugptr1 = current.pWorldState.Get();

		//std::cout << "Open list\n";
		//printOpenList();
		//std::cout << "Closed list\n";
		//printClosedList();
		//std::cout << "\nCurrent is " << current << " : " << (current.action_ == nullptr ? "" : current.action_->name()) << std::endl;

		// Is our current state the goal state? If so, we've found a path, yay.
		if (current.worldState == targetState) {
			TArray<UActionTest*> plan;
			do
			{
				plan.Add(current.pAction.Get());
				auto itr = std::find_if(begin(m_openList), end(m_openList), [&](const NodeRecord& n) { return n.ID == current.parentID; });
				if (itr == end(m_openList))
				{
					itr = std::find_if(begin(m_closedList), end(m_closedList), [&](const NodeRecord& n) { return n.ID == current.parentID; });
				}
				current = *itr;
			} while (current.parentID != 0);
			return plan;
		}

		// Check each node REACHABLE from current -- in other words, where can we go from here?
		for (const auto& potentialAction : actions)
		{
			if (potentialAction->OperableOn(current.worldState))
			{
				auto resultantState = potentialAction->ActOn(current.worldState);

				// Skip if already closed
				if (IsContainedInClosedList(resultantState))
				{
					continue;
				}

				//std::cout << potential_action.name() << " will get us to " << outcome << std::endl;

				// Look for a Node with this WorldState on the open list.
				auto p_outcomeNode = IsContainedInOpenList(resultantState);

				if (p_outcomeNode == end(m_openList))
				{ // not a member of open list
				  // Make a new node, with current as its parent, recording G & H
				  //Node found(outcome, current.g_ + potentialAction.cost(), calculateHeuristic(outcome, goal), current.id_, &potentialAction);
					NodeRecord found(resultantState, potentialAction, current.costSoFar + potentialAction->GetActionCost(), CalculateHeuristic(resultantState, i_pTargetState), current.ID);
					// Add it to the open list (maintaining sort-order therein)
					AddToOpenList(std::move(found));
				}
				else
				{ // already a member of the open list
				  // check if the current G is better than the recorded G
					if (current.costSoFar + potentialAction->GetActionCost() < p_outcomeNode->costSoFar) {
						//std::cout << "My path to " << p_outcome_node->ws_ << " using " << potential_action.name() << " (combined cost " << current.g_ + potential_action.cost() << ") is better than existing (cost " <<  p_outcome_node->g_ << "\n";
						p_outcomeNode->parentID = current.ID;                  // make current its parent
						p_outcomeNode->costSoFar = current.costSoFar + potentialAction->GetActionCost(); // recalc G & H
						p_outcomeNode->estimatedCostToTarget = CalculateHeuristic(current.worldState, i_pTargetState);
						p_outcomeNode->pAction = potentialAction;

						// resort open list to account for the new F
						// sorting likely invalidates the p_outcome_node iterator, but we don't need it anymore
						std::sort(begin(m_openList), end(m_openList));
					}
				}
			}
		}
	}

	// If there's nothing left to evaluate, then we have no possible path left
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "A* planner could not find a path from start to goal");

	return TArray<UActionTest*>();
}

//TArray<TWeakObjectPtr<UActionTest>> UActionPlanner::Plan(TWeakObjectPtr<UWorldState> i_pCurrentState, TWeakObjectPtr<UWorldState> i_pTargetState, const TArray<TWeakObjectPtr<UActionTest>>& actions)
//{
//	if (i_pCurrentState.IsValid() && i_pTargetState.IsValid()) 
//	{
//		if (i_pCurrentState == i_pTargetState)
//		{
//			return TArray<TWeakObjectPtr<UActionTest>>();
//		}
//	}
//
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, "Your World States were invalid!");
//		return TArray<TWeakObjectPtr<UActionTest>>();
//	}
//
//	// Feasible we'd re-use a planner, so clear out the prior results
//	m_openList.clear();
//	m_closedList.clear();
//
//	NodeRecord startNode(i_pCurrentState, nullptr, 0, CalculateHeuristic(i_pCurrentState, i_pTargetState), 0);
//
//	m_openList.push_back(std::move(startNode));
//
//	//int iters = 0;
//	while (m_openList.size() > 0) {
//		//++iters;
//		//std::cout << "\n-----------------------\n";
//		//std::cout << "Iteration " << iters << std::endl;
//
//		// Look for Node with the lowest-F-score on the open list. Switch it to closed,
//		// and hang onto it -- this is our latest node.
//		NodeRecord& current(PopAndClose());
//
//		//std::cout << "Open list\n";
//		//printOpenList();
//		//std::cout << "Closed list\n";
//		//printClosedList();
//		//std::cout << "\nCurrent is " << current << " : " << (current.action_ == nullptr ? "" : current.action_->name()) << std::endl;
//
//		// Is our current state the goal state? If so, we've found a path, yay.
//		if (current.pWorldState == i_pTargetState) {
//			TArray<TWeakObjectPtr<UActionTest>> plan;
//			do 
//			{
//				plan.Add(current.pAction);
//				auto itr = std::find_if(begin(m_openList), end(m_openList), [&](const NodeRecord& n) { return n.ID == current.parentID; });
//				if (itr == end(m_openList)) 
//				{
//					itr = std::find_if(begin(m_closedList), end(m_closedList), [&](const NodeRecord& n) { return n.ID == current.parentID; });
//				}
//				current = *itr;
//			} while (current.parentID != 0);
//			return plan;
//		}
//
//		// Check each node REACHABLE from current -- in other words, where can we go from here?
//		for (const auto& potentialAction : actions) 
//		{
//			if (potentialAction->OperableOn(current.pWorldState)) 
//			{
//				potentialAction->ActOn(current.pWorldState);
//
//				// Skip if already closed
//				if (IsContainedInClosedList(current.pWorldState))
//				{
//					continue;
//				}
//
//				//std::cout << potential_action.name() << " will get us to " << outcome << std::endl;
//
//				// Look for a Node with this WorldState on the open list.
//				auto p_outcomeNode = IsContainedInOpenList(current.pWorldState);
//				
//				if (p_outcomeNode == end(m_openList))
//				{ // not a member of open list
//					// Make a new node, with current as its parent, recording G & H
//					//Node found(outcome, current.g_ + potentialAction.cost(), calculateHeuristic(outcome, goal), current.id_, &potentialAction);
//					NodeRecord found(i_pCurrentState, potentialAction, current.costSoFar + potentialAction->GetActionCost(), CalculateHeuristic(current.pWorldState, i_pTargetState), current.ID);
//					// Add it to the open list (maintaining sort-order therein)
//					AddToOpenList(std::move(found));
//				}
//				else 
//				{ // already a member of the open list
//				 // check if the current G is better than the recorded G
//					if (current.costSoFar + potentialAction->GetActionCost() < p_outcomeNode->costSoFar) {
//						//std::cout << "My path to " << p_outcome_node->ws_ << " using " << potential_action.name() << " (combined cost " << current.g_ + potential_action.cost() << ") is better than existing (cost " <<  p_outcome_node->g_ << "\n";
//						p_outcomeNode->parentID = current.ID;                  // make current its parent
//						p_outcomeNode->costSoFar = current.costSoFar + potentialAction->GetActionCost(); // recalc G & H
//						p_outcomeNode->estimatedCostToTarget = CalculateHeuristic(current.pWorldState, i_pTargetState);
//						p_outcomeNode->pAction = potentialAction;
//
//						// resort open list to account for the new F
//						// sorting likely invalidates the p_outcome_node iterator, but we don't need it anymore
//						std::sort(begin(m_openList), end(m_openList));
//					}
//				}
//			}
//		}
//	}
//
//	// If there's nothing left to evaluate, then we have no possible path left
//	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, "A* planner could not find a path from start to goal");
//	
//	return TArray<TWeakObjectPtr<UActionTest>>();
//}

