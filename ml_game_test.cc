#include <iostream>

#include "ml_game_manager.hh"
#include "ox_game.hh"
#include "random_policy.hh"
#include "console_player.hh"
#include "console_visualizer.hh"
#include "ucb1_policy.hh"

int main(){

  auto GM = ymd::ML_Game_Manager(new ymd::OX_Game{},
				 new ymd::Console_Visualizer{});

  auto ucb1 = new ymd::UCB1_Policy{};
  ucb1->Load("ox_game_ucb1.txt");

  GM.AddPlayer(new ymd::Console_Player{},[](double r){ return r; });
  GM.AddPlayer(ucb1,[](double r){ return -r; });
  // GM.AddPlayer(new ymd::Random_Policy{},
  // 	       [](double r){ return -r; });


  GM.Play();

  return 0;
}
