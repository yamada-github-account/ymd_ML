#include "ml_game_manager.hh"
#include "ox_game.hh"
#include "random_policy.hh"
#include "ucb1_policy.hh"

int main(int argc,char** argv){
  std::size_t N;

  if(argc >= 1){
    N = std::strtoul(argv[1],nullptr,0);
  }


  auto GM1 = ymd::ML_Game_Manager{new ymd::OX_Game{}};
  auto GM2{GM1};
  auto GM3{GM1};

  auto ucb1 = new ymd::UCB1_Policy;
  ucb1->Load("ox_game_ucb1.txt");

  GM1.AddPlayer(ucb1,[](double r){ return r; });
  GM1.AddPlayer(new ymd::Random_Policy{},[](double r){ return -r; });

  GM2.AddPlayer(new ymd::Random_Policy{},[](double r){ return r; });
  GM2.AddPlayer(ucb1,[](double r){ return -r; });

  GM3.AddPlayer(ucb1,[](double r){ return r; });
  GM3.AddPlayer(ucb1,[](double r){ return -r; });

  for(auto i = 0ul; i < N; ++i){
    GM1.Play();
    GM2.Play();
    GM3.Play();
  }

  ucb1->Save("ox_game_ucb1.txt");

  return 0;
}
