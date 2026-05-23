#include <memory>
#include <vector>

#include "neuron.hpp"
#include "value.hpp"

struct LayerSize {
  int n_in_;
  int n_out_;
};
class Layer {
 public:
  Layer(LayerSize s);
  auto operator()(const std::vector<Value>& x) const -> std::vector<Value>;
  [[nodiscard]] auto Parameters() const -> std::weak_ptr<std::vector<Value>> {
    return parameters_;
  };

 private:
  std::vector<Neuron> neurons_;
  std::shared_ptr<std::vector<Value>> parameters_;
};
