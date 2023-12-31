#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"




int piece_square_table[7][2][BOARD_H][BOARD_W] = {{{ 
      //white
      {0, 0, 0, 0, 0}, 
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}, 
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }, {
      //black
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }},{{ // pawn
      //white
      {0, 0, 0, 0, 0},
      {40, 40, 40, 40, 40},
      {10, 0, 30, 0, 10},
      {5, -8, 0, -8, 5},
      {5, 10, -20, 10, 5},
      {0, 0, 0, 0, 0},
    }, {
      //black
      {0, 0, 0, 0, 0},
      {5, 10, -20, 10, 5},
      {5, -8, 0, -8, 5},
      {10, 0, 30, 0, 10},
      {40, 40, 40, 40, 40},
      {0, 0, 0, 0, 0},
    }},{{ // rook
      //white
      {0, 0, 0, 0, 0},
      {5, 10, 10, 10, 5},
      {-5, 0, 0, 0, -5},
      {-5, 0, 0, 0, -5},
      {-5, 0, 0, 0, -5},
      {0, 2, 5, 0, 0},
    }, {
      //black
      {0, 0, 5, 2, 0},
      {-5, 0, 0, 0, -5},
      {-5, 0, 0, 0, -5},
      {-5, 0, 0, 0, -5},
      {5, 10, 10, 10, 5},
      {0, 0, 0, 0, 0},
    }},{{ // knight
      //white
      {-50, -40, -30, -40, -50},
      {-30, 0, 5, 0, -30},
      {-30, 15, 20, 15, -20},
      {-30, 15, 20, 15, -20},
      {-30, 0, 5, 0, -30},
      {-50,-40, -30, -40, -50},
    }, {
      //black
      {-50, -40, -30, -40, -50},
      {-30, 0, 5, 0, -30},
      {-20, 15, 20, 15, -30},
      {-20, 15, 20, 15, -30},
      {-30, 0, 5, 0, -30},
      {-50,-40, -30, -40, -50},
    }},{{ // bishop
      //white
      {-20, -10, -10, -10, -20},
      {-10, 5, 10, 5, -10},
      {-10, 0, 10, 0, -10},
      {-10, 10, 10, 10, -10},
      {-10, 5, 0, 5, -10},
      {-20, -10, -10, -10, -20},
    }, {
      //black
      {-20, -10, -10, -10, -20},
      {-10, 5, 0, 5, -10},
      {-10, 10, 10, 10, -10},
      {-10, 0, 10, 0, -10},
      {-10, 5, 10, 5, -10},
      {-20, -10, -10, -10, -20}
    }},{{ // queen
      //white
      {-20, -10, -5, -10, -20},
      {-10, 0, 0, 0, -10},
      {-5, 0, 5, 0, -5},
      {-5, 0, 5, 0, -5},
      {-10, 5, 0, 0, -10},
      {-20, -10, -5, -10, -20},
    }, {
      //black
      {-20, -10, -5, -10, -20},
      {-10, 0, 0, 5, -10},
      {-5, 0, 5, 0, -5},
      {-5, 0, 5, 0, -5},
      {-10, 0, 0, 0, -10},
      {-20, -10, -5, -10, -20},
    }},{{ // king
      //white
      {-30, -40, -50, -40, -30},
      {-30, -40, -50, -40, -30},
      {-25, -35, -45, -35, -25},
      {-10, -20, -30, -20, -10},
      {20, 0, 0, 0, 20},
      {20, 25, 0, 25, 20},
    }, {
      //black
      {20, 25, 0, 25, 20},
      {20, 0, 0, 0, 20},
      {-10, -20, -30, -20, -10},
      {-25, -35, -45, -35, -25},
      {-30, -40, -50, -40, -30},
      {-30, -40, -50, -40, -30},
    }}};
/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(int self){
  //Basic state-value function
  // [TODO] design your own evaluation function
 
  const int piece_value[7] = {0,89,588,308,319,988,20000}; 
  //0:none, 1:pawn, 2:rook, 3:knight, 4:bishop, 5:Queen, 6:King
  int value = 0;
  for(int i = 0 ; i < BOARD_H ; i++){
    for(int j = 0 ; j < BOARD_W ; j++){
      int current_piece = this->board.board[self][i][j];
      value += (piece_value[current_piece]+piece_square_table[current_piece][self][i][j]);
      

      int opponent_piece = this->board.board[1-self][i][j];
      value -= (piece_value[opponent_piece]+piece_square_table[opponent_piece][1-self][i][j]);
      
    }
  }
  return value;
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  //std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}