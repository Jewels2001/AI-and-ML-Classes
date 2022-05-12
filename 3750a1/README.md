# CPSC 3750 - Artificial Intelligence A1
*Cannibals and Mercenaries river-crossing problem*
By: Julie Wojtiw-Quo
Due February 4th, 11:59pm

## Getting Started

Compile (using **make a1**) and run the project.

##


## Answers to questions:
• Formulate the problem precisely in terms of search, making only those distinctions
necessary to ensure a valid solution. What is the best representation (abstraction) of
a state?

You can represent the state as a three-tuple of integers, listing the number of missionaries, cannibals and boats on one side (the first side) of the river. The other side of the river can be inferred from this state. Since there is only one boat, the third integer in the tuple can be represented by 1 and 0. The initial state would be (3,3,1) and the goal state is (0,0,0). The state space includes all possible locations of missionaries, cannibals and boat(s), with many states that indicate failure. The actions available include loading 1 or 2 people onto a boat, moving the boat, and unloading the boat. The successor function would be to move 1 or 2 people and 1 boat across the river. The cost will be the number of actions taken.

• Implement and solve the problem optimally using an appropriate search algorithm.
Is it a good idea to check for repeated states?

Even though the search space is small, it will save algorithm time by checking for repeated states and not go back to those that have already been visited. By checking for these, excluding the first and last state, there will only be one choice of state to proceed to.

• Why do you think people have a hard time solving this puzzle, given that the state
space is so simple?

A lot of people may not realize that almost all possible states or moves in the puzzle either fail the puzzle or go back to a previous state. Without eliminating repeated states, it will seem like there are many states to choose from without a clear distinct answer/path leading to the goal state.
