#include <vector>

inline std::vector<void (*)()> &features() {
  static std::vector<void (*)()> features;
  return features;
}

struct Register {
  Register(void (*f)()) { features().push_back(f); }
};
