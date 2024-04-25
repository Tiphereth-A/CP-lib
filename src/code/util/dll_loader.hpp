#ifndef TIFALIBS_UTIL_DLL_LOADER
#define TIFALIBS_UTIL_DLL_LOADER

#include "util.hpp"

namespace tifa_libs::util {

// resolves a library at runtime
// you must have ld load the library before using this,
// otherwise it will die and blow up everything
struct DLL {
  char *base;
  std::unordered_map<strn, size_t> syms;
  DLL(const char *file) {
    // obtain symbols of requested library
    char buf[1024];
    strn command = "objdump -T " + strn(file) + " | awk '{if($4 == \".text\") print $7,$1}'";
    auto cmd = popen(command.c_str(), "r");
    while (fgets(buf, 1024, cmd)) {
      std::istringstream ss(buf);
      strn tmp;
      ss >> tmp, ss >> std::hex >> syms[tmp];
    }
    pclose(cmd);

    // obtain base address of requested library
    command = "awk '{if(index($6, \"" + strn(file) + "\") != 0 && $3 == \"00000000\") print substr($1, 1, index($1, \"-\") - 1)}' /proc/" + std::to_string(getpid()) + "/maps";
    cmd = popen(command.c_str(), "r");
    while (fgets(buf, 1024, cmd))
      base = reinterpret_cast<char *>(std::stoul(buf, nullptr, 16));

    pclose(cmd);
  }
  template <TPN R = void, TPN... T>
  CEXP R call(const char *name, T... t) {
    auto off = syms[strn(name)];
    assert(off != 0);
    return ((R(*)(T...))(base + off))(t...);
  }
};

}  // namespace tifa_libs::util

#endif