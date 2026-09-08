#include <abi.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <string>

extern "C" size_t behavior_len(const char *str) { return strlen(str) + 1; }

extern "C" void behavior(const char *str, char *out) {
  auto s = std::string(str);
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  strcpy(out, s.c_str());
}

extern "C" Behavior *Load() {
  Behavior *b = static_cast<Behavior *>(std::malloc(sizeof(Behavior)));
  b->op = behavior;
  b->opl = behavior_len;
  return b;
}

extern "C" void Unload(Behavior *b) { free(b); }
