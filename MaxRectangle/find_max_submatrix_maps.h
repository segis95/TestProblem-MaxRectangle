// A dynamic programming solution.
// Let in the line number h > 0 in position w there is a 1 preceded by k subsequent 1s:
//
// line h: ....1111..11...
//                      ^position w
//
// If for line h-1 for each position v we know the max height of 1s layer for each possible number
// of consequent ones ending in position v, we then are able to dynamically recalculate these values 
// for the line h given the value of k.
// To store pairs <number of consequent 1s ending at position x --> max height of these consequent 1s' series>
// we use an array of maps for each line position.
//
// The algorithm is O(m*n^2logn) and uses O(m*n) of additional memory.

#pragma once
#include "data_structures.h"

Rectangle find_max_submatrix_maps(std::vector<std::vector<bool>>& matrix);
