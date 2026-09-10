#include <abi.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <interface.hpp>
#include <string>

auto GetContext(void *ctx) -> TextProcessor::TextProcessorContext * {
  return reinterpret_cast<TextProcessor::TextProcessorContext *>(ctx);
}

class InternalImpl {
  TextProcessor::TextProcessorContext *ctx;
  size_t op_len(const char *) {}
};

extern "C" size_t foo_len(void *ctx, const char *str) {
  auto c = GetContext(ctx);

  return (strlen(str) * (c->x));
}

extern "C" void foo(void *ctx, const char *str, char *out) {
  auto c = GetContext(ctx);

  auto s = std::string(str);
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  auto f = std::string(s);
  for (size_t i = 0; i < c->x - 1; i++) {
    f += s;
  }

  strcpy(out, f.c_str());
}

extern "C" size_t bar_len(void *ctx, const char *str) {
  auto c = GetContext(ctx);

  return (strlen(str) * (c->x));
}

extern "C" void bar(void *ctx, const char *str, char *out) {
  auto c = GetContext(ctx);

  auto s = std::string(str);
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  auto f = std::string(s);
  for (size_t i = 0; i < c->x - 1; i++) {
    f += s;
  }

  strcpy(out, f.c_str());
}

Impl *CreateFooImpl() {
  auto impl = static_cast<Impl *>(std::malloc(sizeof(Impl)));
  impl->op = foo;
  impl->opl = foo_len;
  return impl;
}

Impl *CreateBarImpl() {
  auto impl = static_cast<Impl *>(std::malloc(sizeof(Impl)));
  impl->op = bar;
  impl->opl = bar_len;
  return impl;
}

class ImplStore {};

extern "C" Behavior *Load(const char *impl_name) {
  Impl *impl;
  auto impl_string = std::string(impl_name);
  if (impl_string == "foo") {
    impl = CreateFooImpl();
  } else if (impl_string == "bar") {
    impl = CreateBarImpl();
  } else {
    return nullptr;
  }
  Behavior *b = static_cast<Behavior *>(std::malloc(sizeof(Behavior)));
  b->impl = impl;

  return b;
}

extern "C" void Unload(Behavior *b) {
  delete b->impl;
  delete b;
}
