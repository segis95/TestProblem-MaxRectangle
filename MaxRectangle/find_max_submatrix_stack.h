// For every position of a line we calculate the number of consequent ones above this position.
// We call these ones a Pile of ones. If there is a 0 above that position, the number of 1s is 0. 
// One can observe the following:
// - If there are less ones above position w than above position w-1, then the (w-1)'s Pile
// cannot be continued to the right;
// - But a Pile starting from position w-1 and having the height of w's Pile can be continued to
// the right;
//
// Example:
// Let two consequent piles are of height 5 and 3 for positions w-1 and w respectively.
// Then the Pile of height 5 cannot be continued to the right, but a Pile of height 3 starting
// at w-1 can be continued to the right until w. ("Pile of 3 interrupts the sequence of Pile of 5").
// We will store "uninterrupted series" of Piles in a stack and update stack in order to preserve
// monotonously increasing Piles heights while we propagate from left to right in a line.
// When necessary we will remove some previous piles to keep piles heights in stack
// monotonously increasing.
//
// Time complexity: O(m*n) because each position is added and deleted into stack no more than once.
// This solution uses O(n) of additional memory.

#pragma once
#include "data_structures.h"

Rectangle find_max_submatrix_stack(std::vector<std::vector<bool>>& matrix);
