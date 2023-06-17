#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./minimax.hpp"

///mnt/c/Users/Yi-Ning/Documents/GitHub/I2P-Chess
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  int maximum = -1e9;
  auto actions = state->legal_actions;
  Move decision ;
  for(auto next_action:actions){
    State *next_state = state->next_state(next_action);
    int score = Minimax::getNodeScore(next_state,depth-1,false);
    if(score > maximum){
        maximum  = score;
        decision = next_action;
    }

  }
  return decision;
}

int Minimax::getNodeScore(State *state, int depth, bool MaximizingPlayer){
     if(!state->legal_actions.size())
        state->get_legal_actions();
    if(depth == 0 || !state->legal_actions.size()){
        return state->evaluate();
    }
    int score = MaximizingPlayer?-1e9:1e9;
    auto actions = state->legal_actions;
    for(auto next_action:actions){
        State *next_state = state->next_state(next_action);
        if(MaximizingPlayer){
            score = std::max(score,getNodeScore(next_state,depth-1,false));
        }else{
            score = std::min(score,getNodeScore(next_state,depth-1,true));
        }
    }
    return score;
   
}