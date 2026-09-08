#include "abi.h"
#include "interface.hpp"
#include "plugin.hpp"
#include <cstddef>
#include <dlfcn.h>
#include <iostream>
#include <print>

int main() {
  // load plugin
  auto plugin = Plugin::LoadPlugin("./bin/debug/lib/libplugin.so");

  // test behavior
  auto t = new TextProcessor(2);
  auto b_handle = plugin->LoadBehavior<TextProcessor::TextProcessorContext>(
      t->GetContext());
  t->SetBehavior(std::move(b_handle));

  std::string text = "Hello World";
  std::string out = t->Execute(text);

  // size_t outlen = behavior->opl(text.data());
  // std::string out = std::string();
  // out.resize(outlen);
  // behavior->op(text.data(), out.data());
  std::println("'{}' -> '{}'", text, out);

  return 0;
}
