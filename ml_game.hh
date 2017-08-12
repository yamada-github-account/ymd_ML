#ifndef YMD_ML_GAME_HH
#define YMD_ML_GAME_HH 1

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

namespace ymd {

  class ML_Game {
  private:
    virtual void Update() = 0;
  protected:
    std::size_t current_state;
    using action_t = std::function<std::size_t(void)>;
    std::shared_ptr<std::unordered_map<std::size_t,std::vector<action_t>>> actions;
    double revenue;
  public:
    ML_Game() = default;
    ML_Game(const ML_Game&) = default;
    ML_Game(ML_Game&&) = default;
    ML_Game& operator=(const ML_Game&) = default;
    ML_Game& operator=(ML_Game&&) = default;
    virtual ~ML_Game() = default;

    const auto CurrentState() noexcept { return current_state; }
    const std::size_t ActionsSize() noexcept {
      if(actions){
	return (*actions)[CurrentState()].size();
      }else{
	return 0ul;
      }
    }
    void TakeAction(std::size_t n){
      if(ActionsSize() <= n){
	std::cerr << "Error: State-" << CurrentState()
		  << " does not have Action-" << n << std::endl;
	return;
      }
      current_state = ((*actions)[CurrentState()])[n]();
      Update();
    }

    virtual bool IsOver() = 0;
    virtual void Initialize() = 0;
    virtual bool ValidPlayers(std::size_t) = 0;
    const auto LastRevenue() noexcept { return revenue; }
    virtual bool Visible() = 0;
    virtual std::string Visualize(){ return std::string{""}; }
    virtual void Reset() = 0;
  }; // class ML_Game

} // namespace ymd
#endif //YMD_ML_GAME_HH
