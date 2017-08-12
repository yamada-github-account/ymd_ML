#ifndef YMD_ML_VISUALIZER_HH
#define YMD_ML_VISUALIZER_HH 1

#include <string>

namespace ymd {
  class ML_Visualizer {
  public:
    ML_Visualizer() = default;
    ML_Visualizer(const ML_Visualizer&) = default;
    ML_Visualizer(ML_Visualizer&&) = default;
    ML_Visualizer& operator=(const ML_Visualizer&) = default;
    ML_Visualizer& operator=(ML_Visualizer&&) = default;
    virtual ~ML_Visualizer() = default;

    virtual void Show(const std::string& s) = 0;
  };
}//namespace ymd
#endif //YMD_ML_VISUALIZER_HH
