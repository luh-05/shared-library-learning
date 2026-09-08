#include <interface.hpp>
#include <plugin.hpp>
#include <print>

int main() {
  // load plugin
  auto plugin = Plugin::LoadPlugin("./bin/debug/lib/libplugin.so");

  // test behavior
  auto t = new TextProcessor(3);
  t->SetBehavior(plugin->LoadBehavior(t->GetContext()));

  std::string text = "Hello World";
  std::string out = t->Execute(text);

  std::println("'{}' -> '{}'", text, out);

  return 0;
}
