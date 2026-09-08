#include "interface.hpp"
#include <abi.h>
#include <cstdlib>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <memory>

using PluginLoad = Behavior *(*)();
using PluginUnload = void (*)(Behavior *b);
struct PluginData {
  void *handle;
  PluginLoad load;
  PluginUnload unload;

  ~PluginData() noexcept { dlclose(this->handle); }
};

class Plugin {
private:
  std::shared_ptr<struct PluginData> data;

public:
  Plugin(std::shared_ptr<PluginData> data) : data(data) {}

  static auto LoadPlugin(const char *path) -> std::unique_ptr<Plugin> {
    void *handle = dlopen(path, RTLD_NOW);

    if (!handle) {
      std::println(std::cerr, "Library '{}' not found!", path);
      std::terminate();
    }

    auto data = std::make_shared<PluginData>();
    data->handle = handle;
    data->load = reinterpret_cast<PluginLoad>(dlsym(handle, "Load"));
    data->unload = reinterpret_cast<PluginUnload>(dlsym(handle, "Unload"));

    if (!data->load || !data->unload) {
      std::println(std::cerr, "Plugin '{}' failed to load!", path);
      std::terminate();
    }

    return std::move(std::make_unique<Plugin>(std::move(data)));
  }

  template <class PluginType>
  auto LoadBehavior(PluginType *context)
      -> std::unique_ptr<BehaviorHandle<PluginType>> {
    std::shared_ptr<PluginData> d = this->data;
    return std::move(std::make_unique<BehaviorHandle<PluginType>>(d, context));
  }
};

template <class PluginType> class BehaviorHandle {
private:
  std::shared_ptr<PluginData> data;
  Behavior *b;

public:
  BehaviorHandle(std::shared_ptr<PluginData> data, PluginType *context)
      : data(data) {
    this->b = this->data->load();
    this->b->context = context;
  }
  ~BehaviorHandle() { this->data->unload(this->b); }

  auto GetBehavior() -> const Behavior * { return this->b; }
};
