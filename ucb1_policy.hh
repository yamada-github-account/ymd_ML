#ifndef YMD_UCB1_POLICY_HH
#define YMD_UCB1_POLICY_HH 1

#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <sstream>

#include "ml_policy.hh"

namespace ymd {
  struct UCB1_Q {
    std::size_t N;
    double R;
    UCB1_Q() = default;
    UCB1_Q(const UCB1_Q&) = default;
    UCB1_Q(UCB1_Q&&) = default;
    UCB1_Q& operator=(const UCB1_Q&) = default;
    UCB1_Q& operator=(UCB1_Q&&) = default;
    ~UCB1_Q() = default;
    UCB1_Q(std::size_t n,double r): N(n),R(r) {}
  };

  class UCB1_Policy : public ML_Policy {
  private:
    using state_id = std::size_t;
    using action_id = std::size_t;
    std::unordered_map<state_id,std::vector<UCB1_Q>> statistic;
    std::vector<std::tuple<state_id,action_id>> selected;
  public:
    UCB1_Policy() = default;
    UCB1_Policy(const UCB1_Policy&) = default;
    UCB1_Policy(UCB1_Policy&&) = default;
    UCB1_Policy& operator=(const UCB1_Policy&) = default;
    UCB1_Policy& operator=(UCB1_Policy&&) = default;
    virtual ~UCB1_Policy() = default;

    virtual void Save(const char* file_name) override {
      std::ofstream file{file_name};
      for(const auto& s: statistic){
	file << (s.first) << " " << (s.second).size() << " ";
	for(const auto q : s.second){
	  file << q.N << " " << q.R << " ";
	}
	file << "\n";
      }
    }
    virtual void Load(const char* file_name) override {
      std::ifstream file{file_name};
      if(! file.is_open()){
	std::cerr << "ERROR: Fail to open file:" << file_name << std::endl;
	return;
      }

      std::stringstream buffer{};
      std::size_t state,actions_size,QN;
      double QR;

      for(std::string line{}; std::getline(file,line);){
	buffer.str(line);
	buffer >> state >> actions_size;

	for(auto i = 0ul; i < actions_size; ++i){
	  buffer >> QN >> QR;
	  statistic[state].emplace_back(QN,QR);
	}
      }

    }

    virtual std::size_t Action(std::size_t state,std::size_t actions_size) override {
      if(statistic[state].empty()){
	std::fill_n(std::back_inserter(statistic[state]),actions_size,UCB1_Q{});
      }

      // Take an action if it has not been tried yet.
      for(auto i=0ul; i < actions_size; ++i){
	if(!(statistic[state][i].N)){
	  selected.emplace_back(state,i);
	  return i;
	}
      }

      auto Nsum = std::accumulate(statistic[state].begin(),statistic[state].end(),
				  0ul,
				  [](auto sum,auto Qnew){ return sum + Qnew.N; });

      std::size_t max_i = std::max_element(statistic[state].begin(),
					   statistic[state].end(),
					   [=,TwoLog=2.0*std::log(1.0*Nsum)]
					   (auto Q1,auto Q2){
					     return (((Q1.R)/(Q1.N)
						      + std::sqrt(TwoLog/(Q1.N))) <
						     ((Q2.R)/(Q2.N)
						      + std::sqrt(TwoLog/(Q2.N))));
					   }) - statistic[state].begin();
      selected.emplace_back(state,max_i);
      return max_i;
    }

    virtual void FeedbackRevenue(double revenue) override {
      for(auto& s : selected){
	auto Qptr = &(statistic[std::get<0>(s)][std::get<1>(s)]);
	++(Qptr->N);
	(Qptr->R) += revenue;
      }

      selected.clear();
    }

  };
}// namespace ymd
#endif //YMD_UCB1_POLICY_HH
