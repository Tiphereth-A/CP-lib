// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/str/suffix_automaton/lib.hpp"

using namespace tifa_libs;
int main() {
  strn s;
  fin >> s;
  suffix_automaton sam;
  for (auto c : s) sam.extend(u32(c - 'a'));
  sam.build(), sam.getsz();
  fout << sam.st[0].sz - 1;
  return 0;
}
