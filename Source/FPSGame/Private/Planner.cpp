// Fill out your copyright notice in the Description page of Project Settings.

#include "Planner.h"
#include "NodeRecord.h"
#include "UActionTest.h"

UPlanner::UPlanner()
{
}

UPlanner::~UPlanner()
{
}

TArray<UActionTest> UPlanner::Plan(const UWorldState& i_currentState, const UWorldState& i_targetState, const TArray<UActionTest>& i_availableActions)
{
	return TArray<UActionTest>();
}

uint8_t UPlanner::EstimateCostToWorldState(const UWorldState& i_currentState, const UWorldState& i_goalState)
{
	return i_currentState.DistanceTo(i_goalState);
}

void UPlanner::AddToOpenList(FNodeRecord&& node)
{
	m_openList.Add(MoveTemp(node));
}

FNodeRecord& UPlanner::TransferToClosedList()
{
	//m_closedList.Push(MoveTemp(m_openList.Pop()));
	m_closedList.Push(m_openList.Pop());

	return m_closedList.Top();
}

bool UPlanner::IsWorldStateInClosedList(const UWorldState& i_state)
{	
	for (auto node : m_closedList)
	{
		if(*(node.p_worldState) == i_state)
		{
			return true;
		}
	}

	return false;
}

bool UPlanner::IsWorldStateInOpenList(const UWorldState& i_state)
{
	for (auto node : m_openList)
	{
		if (*(node.p_worldState) == i_state)
		{
			return true;
		}
	}

	return false;
}
