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
  using Hello = int (*)();

  // Load function as Hello
  auto hello = reinterpret_cast<Hello>(dlsym(handle, "hello"));

  // Check if hello loaded
  if (!hello) {
    std::print(std::cerr, "Function 'hello' not found!");
    return 1;
  }

  // print hello
  std::println("'hello' returned {}", hello());

  // close library
  dlclose(handle);

  return 0;
}
