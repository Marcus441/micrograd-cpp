#include <cstddef>
#include <memory>
#include <print>
#include <vector>

#include "MLP.hpp"
#include "util/graphing.hpp"
#include "value.hpp"

auto ForwardPass(MLP& mlp, const std::vector<std::vector<double>>& xs) -> std::vector<Value> {
  std::vector<Value> preds;
  for (const auto& x : xs) {
    preds.emplace_back(mlp(x));
  }
  return preds;
}

auto ComputeLoss(const std::vector<Value>& preds, const std::vector<double>& y) -> Value {
  Value err_sum_squared{};
  for (size_t i = 0; i < preds.size(); ++i) {
    err_sum_squared = err_sum_squared + (preds[i] - y[i]).Pow(2);
  }
  return err_sum_squared / static_cast<int>(preds.size());
}

auto Step(MLP& mlp, double learning_rate) -> void {
  auto params = mlp.Parameters().lock();
  for (auto& p : *params) {
    p.SetData(p.Data() - (learning_rate * p.Grad()));
  }
  for (auto& p : *params) {
    p.ZeroGrad();
  }
}

auto main() -> int {
  MLP mlp({{.n_in_ = 3, .n_out_ = 4}, {.n_in_ = 4, .n_out_ = 4}, {.n_in_ = 4, .n_out_ = 1}});

  std::vector<std::vector<double>> xs{
      {2.0, 3.0, -1.0}, {3.0, -1.0, 0.5}, {0.5, 1.0, 1.0}, {1.0, 1.0, -1.0}};
  std::vector<double> y{1.0, -1.0, -1.0, 1.0};

  double learning_rate = 0.1;
  int steps = 100;

  for (int s = 0; s < steps; ++s) {
    auto preds = ForwardPass(mlp, xs);
    auto loss = ComputeLoss(preds, y);
    loss.Backward();
    std::println("step {:3} | loss {:.10f}", s, loss.Data());

    if (s == 0) {
      util::graphing::ExportToDot(loss, "before_gradient_descent.dot");
    }

    Step(mlp, learning_rate);
  }

  auto final_preds = ForwardPass(mlp, xs);
  auto final_loss = ComputeLoss(final_preds, y);
  final_loss.Backward();
  util::graphing::ExportToDot(final_loss, "after_gradient_descent.dot");
}
