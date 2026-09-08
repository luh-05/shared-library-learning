
#include "interface.hpp"
#include "abi.h"
#include "plugin.hpp"

TextProcessor::TextProcessor(uint32_t x) {
  this->ctx = std::make_unique<TextProcessorContext>(x);
}

auto TextProcessor::SetBehavior(
    std::unique_ptr<BehaviorHandle<TextProcessorContext>> b) -> void {
  this->behavior = std::move(b);
}

auto TextProcessor::Execute(const std::string &in) -> std::string {
  const Behavior *b = this->behavior->GetBehavior();

  size_t outlen = b->opl(in.data());
  std::string out = std::string();
  out.resize(outlen);
  b->op(in.data(), out.data());

  return std::move(out);
}
