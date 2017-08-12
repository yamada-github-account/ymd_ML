#ifndef YMD_CONSOLE_VISUALIZER_HH
#define YMD_CONSOLE_VISUALIZER_HH 1

#include "ml_visualizer.hh"

namespace ymd {
  class Console_Visualizer : public ML_Visualizer {
  public:
    Console_Visualizer() = default;
    Console_Visualizer(const Console_Visualizer&) = default;
    Console_Visualizer(Console_Visualizer&&) = default;
    Console_Visualizer& operator=(const Console_Visualizer&) = default;
    Console_Visualizer& operator=(Console_Visualizer&&) = default;
    virtual ~Console_Visualizer() = default;

    virtual void Show(const std::string& s) override {
      std::cout << s << std::endl;
    }
  };
} // namespace ymd
#endif //YMD_CONSOLE_VISUALIZER_HH
