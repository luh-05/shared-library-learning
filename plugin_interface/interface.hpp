#pragma once

#include <memory>
#include <stdint.h>
#include <string>
template <class PluginType> class BehaviorHandle;

class TextProcessor {
public:
  typedef struct TextProcessorContext {
    uint32_t x = 0;
  } TextProcessorContext;

  std::unique_ptr<TextProcessorContext> ctx;

  TextProcessor(uint32_t x);

  auto GetContext() -> TextProcessorContext * { return this->ctx.get(); }

  auto SetBehavior(std::unique_ptr<BehaviorHandle<TextProcessorContext>> b)
      -> void;

  auto Execute(const std::string &in) -> std::string;

private:
  std::unique_ptr<BehaviorHandle<TextProcessorContext>> behavior;
};
