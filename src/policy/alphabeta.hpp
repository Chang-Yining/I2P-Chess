#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta{
public:
  static Move get_move(State *state, int depth, int self);
  static int getNodeScore(State *state, int depth, int alpha, int beta, bool MaximizingPlayer, int self);
};