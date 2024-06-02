#include "../../code/util/ndvec.hpp"

#include "../../code/util/traits.hpp"

using std::cout, std::endl, std::operator""s;

template <tifa_libs::container_c T>
std::ostream &operator<<(std::ostream &os, T CR x) {
  if (x.begin() == x.end()) return os << "[]"s;
  os << '[';
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", "s;
  return os << x.back() << ']';
}

#define OUTPUT_(x) cout << #x << ": "s << x << endl

int main() {
  tifa_libs::ndvec<5, int> v(5u, 4u, 3u, 2u, 1u);
  OUTPUT_(v.dim());
  OUTPUT_(v[0].dim());
  OUTPUT_(v[0][0].dim());
  v.fill(42);
  OUTPUT_(v);

  cout << "=========="s << endl;

  tifa_libs::ndvec<5, int> v2(5u, 4u, 0u, 2u, 1u);
  OUTPUT_(v2.dim());
  OUTPUT_(v2);
}
