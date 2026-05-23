#include <memory>
#include <random>
#include <vector>

#include "value.hpp"

class Neuron {
 public:
  Neuron(int n_inputs);
  auto operator()(const std::vector<Value>& x) const -> Value;

  [[nodiscard]] auto Parameters() const -> std::weak_ptr<std::vector<Value>> { return parameters_; }

 private:
  static std::mt19937 rng;
  static std::uniform_real_distribution<double> dist;
  std::shared_ptr<std::vector<Value>> parameters_;
  std::vector<Value> w_;
  Value b_;
};
