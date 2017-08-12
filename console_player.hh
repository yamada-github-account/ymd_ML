#ifndef YMD_CONSOLE_PLAYER_HH
#define YMD_CONSOLE_PLAYER_HH 1

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "ml_policy.hh"

namespace ymd {
  class Console_Player : public ML_Policy {
  public:
    Console_Player() = default;
    Console_Player(const Console_Player&) = default;
    Console_Player(Console_Player&&) = default;
    Console_Player& operator=(const Console_Player&) = default;
    Console_Player& operator=(Console_Player&&) = default;
    virtual ~Console_Player() = default;

    virtual std::size_t Action(std::size_t state,std::size_t actions_size){
      std::cout << "State-" << state << ". Possible Actions [0,"
		<< actions_size << ")" << std::endl;
      std::size_t key = std::numeric_limits<std::size_t>::max();
      std::string buffer{};

      while(true){
	std::cout << "Select Action: " << std::flush;
	std::cin >> buffer;

	if(std::all_of(buffer.begin(),buffer.end(),
		       [](auto c){ return '0' <= c && c <= '9'; })){

	  key = std::stoul(buffer);
	  if(key < actions_size){ break; }
	}

	std::cerr << "You must specify in [0," << actions_size << ")" << std::endl;
      }
      return key;
    }

    virtual void FeedbackRevenue(double revenue){
      std::cout << (revenue > 0 ? "You Win!" :"You Lose!") << std::endl;
    }

  };
} //namespace ymd
#endif //YMD_CONSOLE_PLAYER_HH
