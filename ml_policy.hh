#ifndef YMD_ML_POLICY_HH
#define YMD_ML_POLICY_HH 1

namespace ymd {

  class ML_Policy {
  public:
    ML_Policy() = default;
    ML_Policy(const ML_Policy&) = default;
    ML_Policy(ML_Policy&&) = default;
    ML_Policy& operator=(const ML_Policy&) = default;
    ML_Policy& operator=(ML_Policy&&) = default;
    virtual ~ML_Policy() = default;

    virtual void Save(const char*){}
    virtual void Load(const char*){}

    virtual std::size_t Action(std::size_t state,std::size_t actions_size) = 0;
    virtual void FeedbackRevenue(double revenue) = 0;
  };
} // namespace ymd
#endif //YMD_ML_POLICY_HH
