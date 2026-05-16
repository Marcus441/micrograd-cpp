#include <cstddef>
#include <print>
#include <vector>

#include "MLP.hpp"
#include "util/graphing.hpp"
#include "value.hpp"

auto main() -> int {
  MLP n_mlp =
      MLP({{.n_in_ = 3, .n_out_ = 4}, {.n_in_ = 4, .n_out_ = 4}, {.n_in_ = 4, .n_out_ = 1}});
  std::vector<double> x0{2, 3.0, -1.0};
  std::vector<double> x1{3.0, -1.0, 0.5};
  std::vector<double> x2{0.5, 1.0, 1.0};
  std::vector<double> x3{1.0, 1.0, -1.0};

  std::vector<double> y{1.0, -1.0, -1.0, 1.0};

  std::vector<Value> output_pred;
  output_pred.emplace_back(n_mlp(x0));
  output_pred.emplace_back(n_mlp(x1));
  output_pred.emplace_back(n_mlp(x2));
  output_pred.emplace_back(n_mlp(x3));

  int n = 4;  // number of input vectors
  Value err_sum_squared{};
  for (size_t i = 0; i < (size_t)n; ++i) {
    err_sum_squared = err_sum_squared + (output_pred[i] - y[i]).Pow(2);
  }
  Value loss = err_sum_squared / n;
  std::println("loss before backward {:.2}", loss.Data());
  loss.Backward();
  util::graphing::ExportToDot(loss, "file.dot");
  std::println("loss after backward {:.2}", loss.Data());

  return 0;
}
