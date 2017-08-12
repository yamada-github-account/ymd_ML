#ifndef YMD_ML_GAME_MANAGER_HH
#define YMD_ML_GAME_MANAGER_HH 1

#include <tuple>
#include <vector>

#include "ml_game.hh"
#include "ml_policy.hh"
#include "ml_visualizer.hh"

namespace ymd {
  class ML_Game_Manager {
  private:
    ML_Game* game;
    using ML_Revenue = std::function<double(double)>;
    std::vector<std::tuple<ML_Policy*,ML_Revenue>> players;
    std::shared_ptr<ML_Visualizer> visualizer;
  public:
    ML_Game_Manager() = default;
    ML_Game_Manager(const ML_Game_Manager&) = default;
    ML_Game_Manager(ML_Game_Manager&&) = default;
    ML_Game_Manager& operator=(const ML_Game_Manager&) = default;
    ML_Game_Manager& operator=(ML_Game_Manager&&) = default;
    virtual ~ML_Game_Manager() = default;

    ML_Game_Manager(ML_Game* g,ML_Visualizer* v = nullptr): game(g), visualizer(v){
      g->Initialize();
    }

    auto AddPlayer(ML_Policy* p,ML_Revenue&& r){
      players.emplace_back(p,r);
    }

    auto Play(){
      if(! game->ValidPlayers(players.size())){
	std::cerr << "This game cannot be played by "
		  << players.size() << " players." << std::endl;
	return;
      }

      auto current_player = players.begin();
      while(!(game->IsOver())){

	game->TakeAction(std::get<0>(*current_player)->Action(game->CurrentState(),
							      game->ActionsSize()));

	if(visualizer && (game->Visible())){
	  visualizer->Show(game->Visualize());
	}

	++current_player;
	if(players.end() == current_player){
	  current_player = players.begin();
	}
      } // while(!(game->IsOver()))

      for(auto& p : players){
	std::get<0>(p)->FeedbackRevenue(std::get<1>(p)(game->LastRevenue()));
      }
    }
  }; // class ML_Game_Manager

} // namespace ymd
#endif //YMD_ML_GAME_MANAGER_HH
