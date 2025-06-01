#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/str/suffix_automaton.hpp"

using namespace tifa_libs;
int main() {
  strn s;
  fin >> s;
  str::suffix_automaton sam;
  for (auto c : s) sam.extend(u32(c - 'a'));
  sam.build(), sam.getsz();
  fout << sam.st[0].sz - 1;
  return 0;
}
