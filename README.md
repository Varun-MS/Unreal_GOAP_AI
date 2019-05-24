# Unreal GOAP AI
A simple Goal Oriented Action Planner implemented for Unreal Engine 4.

This project is a work in progress.


<b>The Planner</b>

The Planner, written in C++ utilizes a variation of A* pathfinding to traverse through a "graph" of action nodes where each node represents an Action that can be performed by an AI entity. When a particular goal is set to be achieved, the planner utilizes the current world state to device a set of actions or plan to achieve that goal. 


<b>Action</b>

Each action requires a set of preconditions to be met (defined as world state variables). These preconditions, or world state variables (boolean values) represent the state of the game world as seen by an AI entity. Performing an action results in a set of postconditions or effects. These are nothing but modifications of the preconditions supplied to the action as well as some other world state variables that may have been modified.


<b>Action Manager</b>

The Action Manager is responsible for exectuing the set of actions that constitute a plan (in the order that they are recieved). It also makes sure to prioritize plans based on their importance (removing low priority plans in favor of higher priority ones)


<b>Blackboard (TODO)</b>

The Blackboard, much like the one used by UE4 Behavior Tree, is responsible for holding world and local data to be used by the actions when they are being executed.
