#include "plugin.hpp"
#include <abi.h>
#include <interface.hpp>

TextProcessor::TextProcessor(uint32_t x) {
  this->ctx = std::make_unique<TextProcessorContext>(x);
}

auto TextProcessor::SetBehavior(PluginHandle b) -> void {
  this->behavior = std::move(b);
}

auto TextProcessor::Execute(const std::string &in) -> std::string {
  const auto b = this->behavior->GetBehavior();

  size_t outlen = this->behavior->behavior_len(in);
  std::string out = std::string();
  out.resize(outlen);
  this->behavior->behavior(in, out);
  return out;
}
