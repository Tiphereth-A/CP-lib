#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/str/suffix_automaton.hpp"

int main() {
  strn s;
  tifa_libs::fin >> s;
  tifa_libs::str::suffix_automaton sam;
  for (auto c : s) sam.extend(c - 'a');
  sam.build(), sam.getsz();
  tifa_libs::fout << sam.st[0].sz - 1;
  return 0;
}
