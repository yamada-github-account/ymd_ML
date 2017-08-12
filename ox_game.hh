#ifndef YMD_OX_GAME_HH
#define YMD_OX_GAME_HH 1

#include <type_traits>

#include "ml_game.hh"

namespace ymd {
  class OX_Game : public ML_Game {
  private:
    int cells[9];

    static constexpr auto is_inside(std::size_t i) noexcept { return i < 9; }
    auto are_aligned(std::size_t i,std::size_t j,std::size_t k) const noexcept {
      if(is_inside(i) && is_inside(j) && is_inside(k)) {
	  return (cells[i] + cells[j] + cells[k])/3;
      }
	return 0;
    }

    auto encode() noexcept {
      std::size_t id = 0;
      std::size_t power = 1;

      if(! IsValid()){ current_state = -1; }

      for(auto& d : cells){
	id += (d+1)*power;
	power *= 3;
      }

      current_state = id;
    }
    virtual void Update() override {
      std::size_t id = CurrentState();
      for(auto& c : cells){
	c = (id%3 - 1);
	id /= 3;
      }
    }
  public:
    OX_Game() = default;
    OX_Game(const OX_Game&) = default;
    OX_Game(OX_Game&&) = default;
    OX_Game& operator=(const OX_Game&) = default;
    OX_Game& operator=(OX_Game&&) = default;
    virtual ~OX_Game() = default;

    bool IsValid() const noexcept {
      for(const auto& c: cells){ if(c < -1 || c > 1){ return false; } }
      return true;
    }

    auto GameWinner() const noexcept {
      auto winner = 0;

      // check row
      if(winner = are_aligned(0,1,2)){ return winner; }
      if(winner = are_aligned(3,4,5)){ return winner; }
      if(winner = are_aligned(6,7,8)){ return winner; }

      // check column
      if(winner = are_aligned(0,3,6)){ return winner; }
      if(winner = are_aligned(1,4,7)){ return winner; }
      if(winner = are_aligned(2,5,8)){ return winner; }

      // check diagonal
      if(winner = are_aligned(0,4,8)){ return winner; }
      if(winner = are_aligned(2,4,6)){ return winner; }

      // non of them are winner
      return winner;
    }

    virtual bool IsOver() override {
      auto winner = GameWinner();

      revenue = winner;
      return winner ? true : false;
    }

    auto Next() const noexcept {
      if(! IsValid()){ return 0; }

      auto sum = 0;
      for(auto& d : cells){ sum += d; }

      return 1 - 2*sum;
    }

    virtual void Initialize() override {
      encode();

      if(! actions){ actions = std::make_shared<decltype(actions)::element_type>(); }

      if(! (*actions)[CurrentState()].empty()){ return; }
      if(IsOver()){ return; }

      for(auto& c : cells){
	if(c){ continue; }

	c = Next();
	OX_Game copy{*this};
	c = 0;

	copy.encode();

	(*actions)[CurrentState()].push_back([id=copy.CurrentState()](){return id;});

	copy.Initialize();
      }

    }

    virtual bool ValidPlayers(std::size_t n) override {
      return (2 == n);
    }

    int At(std::size_t i) const noexcept {
      if(is_inside(i)){ return cells[i]; }

      return 0;
    }

    void Fill(std::size_t i) noexcept {
      if(is_inside(i) && !(cells[i])){
	cells[i] = Next();
      }
      encode();
    }

    virtual bool Visible() override { return true; }
    virtual std::string Visualize() override {
      static const char mark[3] = {'x',' ','o'};

      std::string visual{"_______\n|"};
      visual += mark[cells[0]+1];
      visual += '|';
      visual += mark[cells[1]+1];
      visual += '|';
      visual += mark[cells[2]+1];
      visual += "|\n|";
      visual += mark[cells[3]+1];
      visual += '|';
      visual += mark[cells[4]+1];
      visual += '|';
      visual += mark[cells[5]+1];
      visual += "|\n|";
      visual += mark[cells[6]+1];
      visual += '|';
      visual += mark[cells[7]+1];
      visual += '|';
      visual += mark[cells[8]+1];
      visual += "|\n-------\n";
      return visual;
    }
  };

} // namespace ymd

#endif //YMD_OX_GAME_HH
