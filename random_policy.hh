#ifndef YMD_RANDOM_POLICY_HH
#define YMD_RANDOM_POLICY_HH 1

#include <random>

#include "ml_policy.hh"

namespace ymd {

  class Random_Policy : public ML_Policy {
  private:
    std::function<std::size_t(std::size_t)> random;
  public:
    using dist_t = std::uniform_int_distribution<std::size_t>;
    Random_Policy() : random([g=std::mt19937{std::random_device{}()},
			      d=dist_t{}](std::size_t n) mutable {
			       return d(g,dist_t::param_type(0,n-1));
			     }) {}
    Random_Policy(const Random_Policy&) = default;
    Random_Policy(Random_Policy&&) = default;
    Random_Policy& operator=(const Random_Policy&) = default;
    Random_Policy& operator=(Random_Policy&&) = default;
    virtual ~Random_Policy() = default;

    virtual std::size_t Action(std::size_t state,std::size_t actions_size) override {
      return random(actions_size);
    }
    virtual void FeedbackRevenue(double revenue) override {}

  };
} // namespace ymd
#endif //YMD_RANDOM_POLICY_HH
