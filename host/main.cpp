#include "abi.h"
#include <cstddef>
#include <dlfcn.h>
#include <iostream>
#include <print>

int main() {
  // Open library
  void *handle = dlopen("./bin/debug/lib/libplugin.so", RTLD_NOW);

  // Check if library loaded
  if (!handle) {
    std::println(std::cerr, "Library not found!");
    return 1;
  }

  using PluginGet = Behavior *(*)();

  auto plugin_get = reinterpret_cast<PluginGet>(dlsym(handle, "Get"));

  // Check if behavior loaded
  if (!plugin_get) {
    std::println(std::cerr, "PluginGet not found!");
    return 1;
  }

  auto behavior = plugin_get();

  // print behavior("Hello World")
  std::string text = "Hello World";
  size_t outlen = behavior->opl(text.data());
  std::string out = std::string();
  out.resize(outlen);
  behavior->op(text.data(), out.data());
  std::println("'{}' -> '{}'", text, out);

  // close library
  dlclose(handle);

  return 0;
}
