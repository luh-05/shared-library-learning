#pragma once

#include <memory>
#include <stdint.h>
#include <string>

template <class PluginType> class BehaviorHandle;

class TextProcessor {
public:
  typedef struct TextProcessorContext {
    uint32_t x;
  } TextProcessorContext;
  using PluginHandle = std::unique_ptr<BehaviorHandle<TextProcessorContext>>;

  std::unique_ptr<TextProcessorContext> ctx;

  TextProcessor(uint32_t x);

  auto GetContext() -> TextProcessorContext * { return this->ctx.get(); }

  auto SetBehavior(PluginHandle b) -> void;

  auto Execute(const std::string &in) -> std::string;

private:
  PluginHandle behavior;
};
