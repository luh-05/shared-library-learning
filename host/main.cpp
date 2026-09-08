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

  // Define function pointer type according to C ABI
  using Behavior = void (*)(const char *, char *);
  using BehaviorLen = size_t (*)(const char *);

  // Load function as Behavior
  auto behavior = reinterpret_cast<Behavior>(dlsym(handle, "behavior"));

  // Check if behavior loaded
  if (!behavior) {
    std::println(std::cerr, "Behavior not found!");
    return 1;
  }

  // Load function as BehaviorLen
  auto behavior_len =
      reinterpret_cast<BehaviorLen>(dlsym(handle, "behavior_len"));

  // Check if behavior_len loaded
  if (!behavior_len) {
    std::println(std::cerr, "BehaviorLen not found!");
    return 1;
  }

  // print behavior("Hello World")
  std::string text = "Hello World";
  size_t outlen = behavior_len(text.data());
  std::string out = std::string();
  out.resize(outlen);
  behavior(text.data(), out.data());
  std::println("behavior('{}') returned '{}'", text, out);

  // close library
  dlclose(handle);

  return 0;
}
