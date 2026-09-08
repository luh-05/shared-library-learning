#include "abi.h"
#include "plugin.hpp"
#include <cstddef>
#include <dlfcn.h>
#include <iostream>
#include <print>

int main() {
  // load plugin
  auto plugin = Plugin::LoadPlugin("./bin/debug/lib/libplugin.so");

  // get behavior
  auto behavior = plugin->GetBehavior();

  // test behavior
  std::string text = "Hello World";
  size_t outlen = behavior->opl(text.data());
  std::string out = std::string();
  out.resize(outlen);
  behavior->op(text.data(), out.data());
  std::println("'{}' -> '{}'", text, out);

  return 0;
}
