#include "interface.hpp"
#include "plugin.hpp"
#include <dlfcn.h>
#include <print>

int main() {
  // load plugin
  auto plugin = Plugin::LoadPlugin("./bin/debug/lib/libplugin.so");

  // test behavior
  auto t = new TextProcessor(3);
  auto b_handle = plugin->LoadBehavior<TextProcessor::TextProcessorContext>(
      t->GetContext());
  t->SetBehavior(std::move(b_handle));

  std::string text = "Hello World";
  std::string out = t->Execute(text);

  std::println("'{}' -> '{}'", text, out);

  return 0;
}
