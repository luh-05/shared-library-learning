#include <abi.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <interface.hpp>
#include <string>

Behavior *b;

extern "C" size_t behavior_len(const char *str);
extern "C" void behavior(const char *str, char *out);

extern "C" Behavior *Load() {
  b = static_cast<Behavior *>(std::malloc(sizeof(Behavior)));
  b->op = behavior;
  b->opl = behavior_len;
  return b;
}

extern "C" void Unload() {
  if (b) {
    delete b;
  }
}

auto GetContext() {
  return reinterpret_cast<TextProcessor::TextProcessorContext *>(b->context);
}

extern "C" size_t behavior_len(const char *str) {
  auto ctx = GetContext();
  return (strlen(str) * (ctx->x));
}

extern "C" void behavior(const char *str, char *out) {
  auto s = std::string(str);
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  auto ctx = GetContext();

  auto f = std::string(s);
  for (size_t i = 0; i < ctx->x - 1; i++) {
    f += s;
  }

  strcpy(out, f.c_str());
}
