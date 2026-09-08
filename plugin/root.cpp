#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <cstddef>
#include <string>

extern "C" size_t behavior_len(const char *str) { return strlen(str); }

extern "C" void behavior(const char *str, char *out) {
  auto s = std::string(str);
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  strcpy(out, s.c_str());
}
