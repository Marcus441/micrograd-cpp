#include <initializer_list>
#include <memory>
#include <vector>

#include "layer.hpp"

class MLP {
 public:
  MLP(std::initializer_list<LayerSize> sizes);
  auto operator()(std::vector<double> x) -> Value;
  [[nodiscard]] auto Parameters() const -> std::weak_ptr<std::vector<Value>> {
    return parameters_;
  };

 private:
  std::vector<Layer> layers_;
  std::shared_ptr<std::vector<Value>> parameters_;
};
