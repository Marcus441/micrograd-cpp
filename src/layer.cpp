#include "layer.hpp"

#include <vector>

#include "value.hpp"

Layer::Layer(LayerSize s) {
  parameters_ = std::make_shared<std::vector<Value>>();
  for (int i = 0; i < s.n_out_; ++i) {
    neurons_.emplace_back(s.n_in_);
    auto neuron_params = neurons_.back().Parameters().lock();
    parameters_->insert(parameters_->end(), neuron_params->begin(), neuron_params->end());
  }
}

auto Layer::operator()(const std::vector<Value>& x) const -> std::vector<Value> {
  std::vector<Value> out;
  for (const auto& neuron : neurons_) {
    out.emplace_back(neuron(x));
  }
  return out;
}
