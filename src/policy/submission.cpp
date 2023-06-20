#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./alphabeta.hpp"

///mnt/c/Users/Yi-Ning/Documents/GitHub/I2P-Chess
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth, int self){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  int maximum = -1e9;
  auto actions = state->legal_actions;
  Move decision ;
  for(auto next_action:actions){
    State *next_state = state->next_state(next_action);
    int score = Alphabeta::getNodeScore(next_state,depth-1, -1e9 , 1e9,false, self);
    if(score > maximum){
        maximum  = score;
        decision = next_action;
    }

  }
  return decision;
}

int Alphabeta::getNodeScore(State *state, int depth, int alpha, int beta, bool MaximizingPlayer, int self){
     if(!state->legal_actions.size())
        state->get_legal_actions();
    if(depth == 0 || !state->legal_actions.size()){
        return state->evaluate(self);
    }
    int score = MaximizingPlayer?-1e9:1e9;
    auto actions = state->legal_actions;
    for(auto next_action:actions){
        State *next_state = state->next_state(next_action);
        if(MaximizingPlayer){
            score = std::max(score,getNodeScore(next_state,depth-1,alpha, beta, false, self));
            alpha = std::max(alpha, score);
            if(alpha >= beta)
                break;
        }else{
            score = std::min(score,getNodeScore(next_state,depth-1,alpha,beta,true, self));
            beta = std::min(beta, score);
            if(beta <= alpha)
                break;
        }
    }
    return score;
   
}