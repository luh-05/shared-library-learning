#include <abi.h>
#include <dlfcn.h>
#include <exception>
#include <interface.hpp>
#include <iostream>
#include <memory>

#pragma once

using PluginLoad = Behavior *(*)(const char *impl_name);
using PluginUnload = void (*)(Behavior *);
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

    return std::make_unique<Plugin>(std::move(data));
  }

  template <class PluginType>
  auto LoadBehavior(PluginType *context, std::string impl_name)
      -> std::unique_ptr<BehaviorHandle<PluginType>> {
    std::shared_ptr<PluginData> d = this->data;
    return std::make_unique<BehaviorHandle<PluginType>>(d, context, impl_name);
  }
};

template <class PluginType> class BehaviorHandle {
private:
  std::shared_ptr<PluginData> data;
  Behavior *b;

public:
  BehaviorHandle(std::shared_ptr<PluginData> data, PluginType *context,
                 std::string impl_name)
      : data(data) {
    this->b = this->data->load(impl_name.data());
    if (!this->b) {
      std::println(std::cerr, "Implementation '{}' could not be found!",
                   impl_name);
      std::terminate();
    }
    this->b->context = context;
  }
  ~BehaviorHandle() { this->data->unload(this->b); }

  auto GetBehavior() -> const Behavior * { return this->b; }

  size_t behavior_len(std::string_view text) {
    return this->b->impl->opl(this->b->context, text.data());
  }

  void behavior(std::string_view in, std::string &out) {
    this->b->impl->op(this->b->context, in.data(), out.data());
  }
};
