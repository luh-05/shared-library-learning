#include <abi.h>
#include <cstdlib>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <memory>

class Plugin {
private:
  using PluginLoad = Behavior *(*)();
  using PluginUnload = void (*)(Behavior *b);

  struct PluginData {
    void *handle;
    PluginLoad load;
    PluginUnload unload;

    Behavior *b;
  };

  std::unique_ptr<struct PluginData> data;

public:
  Plugin(struct PluginData *data)
      : data(std::unique_ptr<struct PluginData>(data)) {
    this->data->b = this->data->load();
  }
  ~Plugin() noexcept {
    this->data->unload(this->data->b);
    dlclose(this->data->handle);
  }

  static auto LoadPlugin(const char *path) -> std::unique_ptr<Plugin> {
    void *handle = dlopen(path, RTLD_NOW);

    if (!handle) {
      std::println(std::cerr, "Library '{}' not found!", path);
      std::terminate();
    }

    auto data = reinterpret_cast<struct PluginData *>(
        std::malloc(sizeof(struct PluginData)));
    data->handle = handle;
    data->load = reinterpret_cast<PluginLoad>(dlsym(handle, "Load"));
    data->unload = reinterpret_cast<PluginUnload>(dlsym(handle, "Unload"));

    if (!data->load || !data->unload) {
      std::println(std::cerr, "Plugin '{}' failed to load!", path);
      std::terminate();
    }

    return std::move(std::make_unique<Plugin>(data));
  }

  auto GetBehavior() -> const Behavior * { return this->data->b; }
};
