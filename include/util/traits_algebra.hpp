#ifndef TIFALIBS_UTIL_TRAITS_ALGEBRA
#define TIFALIBS_UTIL_TRAITS_ALGEBRA
// clang-format off
#include "util.hpp"

namespace tifa_libs {

#ifndef CHECK_ALGEBRA_
#ifdef ONLINE_JUDGE
#define CHECK_ALGEBRA_ false
#else
#define CHECK_ALGEBRA_ true
#endif
#endif
template <class T, auto op> concept binary_c = requires(T x, T y) { op(x, y); };
template <class T, auto op> concept relation_c = requires(T x, T y) { { op(x, y) } -> std::same_as<bool>; };
template <class T, class R, auto mapping> concept left_mapping_c = requires(T x, R k) { mapping(k, x); };
template <class T, class R, auto mapping> concept right_mapping_c = requires(T x, R k) { mapping(x, k); };
template <class T, class R, auto mapping> concept mapping_c = left_mapping_c<T, R, mapping> || right_mapping_c<T, R, mapping>;
template <class T, auto op> requires binary_c<T, op>
#define MERGE_(name, ...) static CEXP bool name = (__VA_ARGS__ && (left_##name || right_##name)) || (left_##name && right_##name)
struct properites_optt {  // $\forall$ omitted
  static CEXP bool associativity = false;  // $\operatorname{op}(\operatorname{op}(x,y),z)=\operatorname{op}(x,\operatorname{op}(y,z))$
  static CEXP bool commutativity = false;  // $\operatorname{op}(x,y)=\operatorname{op}(y,x)$
  static CEXP bool idempotency = false;  // $\operatorname{op}(x,x)=x$
  static CEXP bool left_identity = false;   // $\exists e, \operatorname{op}(e,x)=x$
  static CEXP bool right_identity = false;  // $\exists e, \operatorname{op}(x,e)=x$
  MERGE_(identity, commutativity);
  static CEXP bool left_nil = false;   // $\exists 0, \operatorname{op}(0,x)=0$
  static CEXP bool right_nil = false;  // $\exists 0, \operatorname{op}(x,0)=0$
  MERGE_(nil, commutativity);
  static CEXP bool nilpotency = nil && false;  // $\exists n>0, x^n=0; x^1:=x, x^n:=\operatorname{op}(x^{n-1},x)$
  static CEXP bool left_non_zero_divisor = left_nil && false;    // $\forall a\ne 0, \nexists b\ne 0, \operatorname{op}(b,a)=0$
  static CEXP bool right_non_zero_divisor = right_nil && false;  // $\forall a\ne 0, \nexists b\ne 0, \operatorname{op}(a,b)=0$
  MERGE_(non_zero_divisor, commutativity);
  static CEXP bool left_divisibility = false;   // $\exists! x, \operatorname{op}(a,x)=b$
  static CEXP bool right_divisibility = false;  // $\exists! y, \operatorname{op}(y,a)=b$
  MERGE_(divisibility, commutativity);
  static CEXP bool left_invertiblity = left_identity && left_divisibility;     // $\exists! y, \operatorname{op}(y,x)=e$
  static CEXP bool right_invertiblity = right_identity && right_divisibility;  // $\exists! y, \operatorname{op}(x,y)=e$
  MERGE_(invertiblity, commutativity);
};
template <class T, auto op, auto op2> requires binary_c<T, op> && binary_c<T, op2>
struct properites_optt_op2tt {  // $\forall$ omitted
  static CEXP bool left_distributivity = false;   // $\operatorname{op2}(a,\operatorname{op}(b,c))=\operatorname{op}(\operatorname{op2}(a,b),\operatorname{op2}(a,c))$
  static CEXP bool right_distributivity = false;  // $\operatorname{op2}(\operatorname{op}(b,c),a)=\operatorname{op}(\operatorname{op2}(b,a),\operatorname{op2}(c,a))$
  MERGE_(distributivity, properites_optt<T, op2>::commutativity);
  static CEXP bool left_absorption = false;   // $\operatorname{op}(a,\operatorname{op2}(a,b))=b, \operatorname{op2}(a,\operatorname{op}(a,b))=b$
  static CEXP bool right_absorption = false;  // $\operatorname{op}(\operatorname{op2}(b,a),a)=b, \operatorname{op2}(\operatorname{op}(b,a),a)=b$
  MERGE_(absorption, properites_optt<T, op>::commutativity && properites_optt<T, op2>::commutativity);
};
#undef MERGE_
template <class T, class R, auto mapping> requires mapping_c<T, R, mapping>
struct properites_mp {  // $\forall$ omitted
  // left: $\operatorname{mapping}(1,x)=x$
  // right: $\operatorname{mapping}(x,1)=x$
  static CEXP bool identity = false;
};
template <class T, class R, auto op, auto mapping> requires binary_c<T, op> && mapping_c<T, R, mapping>
struct properites_optt_mp {  // $\forall$ omitted
  // left: $\operatorname{mapping}(k,\operatorname{op}(a,b))=\operatorname{op}(\operatorname{mapping}(k,a),\operatorname{mapping}(k,b))$
  // right: $\operatorname{mapping}(\operatorname{op}(a,b),k)=\operatorname{op}(\operatorname{mapping}(a,k),\operatorname{mapping}(b,k))$
  static CEXP bool distributivity = false;
};
template <class T, class R, auto op, auto mapping> requires binary_c<R, op> && mapping_c<T, R, mapping>
struct properites_oprr_mp {  // $\forall$ omitted
  // left: $\operatorname{mapping}(\operatorname{op}(k,l),a)=\operatorname{mapping}(k,\operatorname{mapping}(l,a))$
  // right: $\operatorname{mapping}(a,\operatorname{op}(k,l))=\operatorname{mapping}(\operatorname{mapping}(l,a),k)$
  static CEXP bool associativity = false;
};
template <class T, class R, auto op, auto op2, auto mapping> requires binary_c<T, op> && binary_c<R, op2> && mapping_c<T, R, mapping>
struct properites_optt_op2rr_mp {  // $\forall$ omitted
  // left: $\operatorname{mapping}(\operatorname{op2}(k,l),a)=\operatorname{op}(\operatorname{mapping}(k,a),\operatorname{mapping}(l,a))$
  // right: $\operatorname{mapping}(a,\operatorname{op2}(k,l))=\operatorname{op}(\operatorname{mapping}(a,k),\operatorname{mapping}(a,l))$
  static CEXP bool distributivity = false;
};
// group-like
template <class T, auto op> concept magma_c = !CHECK_ALGEBRA_ || (binary_c<T, op>);
template <class T, auto op> concept semigroup_c = !CHECK_ALGEBRA_ || (magma_c<T, op> && properites_optt<T, op>::associativity);
template <class T, auto op> concept quasigroup_c = !CHECK_ALGEBRA_ || (magma_c<T, op> && properites_optt<T, op>::divisibility);
template <class T, auto op> concept unital_magma_c = !CHECK_ALGEBRA_ || (magma_c<T, op> && properites_optt<T, op>::identity);
template <class T, auto op> concept monoid_c = !CHECK_ALGEBRA_ || (semigroup_c<T, op> && properites_optt<T, op>::identity);
template <class T, auto op> concept loop_c = !CHECK_ALGEBRA_ || (unital_magma_c<T, op> && properites_optt<T, op>::divisibility);
template <class T, auto op> concept associative_quasigroup_c = !CHECK_ALGEBRA_ || (quasigroup_c<T, op> && properites_optt<T, op>::associativity);
template <class T, auto op> concept group_c = !CHECK_ALGEBRA_ || (semigroup_c<T, op> && properites_optt<T, op>::divisibility);
template <class T, auto op> concept abelian_group_c = !CHECK_ALGEBRA_ || (group_c<T, op> && properites_optt<T, op>::commutativity);
// lattice-like
template <class T, auto op> concept semilattice_c = !CHECK_ALGEBRA_ || (magma_c<T, op> && properites_optt<T, op>::associativity && properites_optt<T, op>::commutativity && properites_optt<T, op>::idempotency);
template <class T, auto join, auto meet> concept lattice_c = !CHECK_ALGEBRA_ || (semilattice_c<T, join> && semilattice_c<T, meet> && properites_optt_op2tt<T, join, meet>::absorption);
template <class T, auto join, auto meet> concept distributive_lattice_c = !CHECK_ALGEBRA_ || (lattice_c<T, join, meet> && properites_optt_op2tt<T, join, meet>::distributivity && properites_optt_op2tt<T, meet, join>::distributivity);
// ring-like
template <class T, auto add, auto mul> concept left_nearring_c = !CHECK_ALGEBRA_ || (group_c<T, add> && semigroup_c<T, mul> && properites_optt_op2tt<T, add, mul>::left_distributivity);
template <class T, auto add, auto mul> concept right_nearring_c = !CHECK_ALGEBRA_ || (group_c<T, add> && semigroup_c<T, mul> && properites_optt_op2tt<T, add, mul>::right_distributivity);
template <class T, auto add, auto mul> concept rng_c = !CHECK_ALGEBRA_ || (left_nearring_c<T, add, mul> && right_nearring_c<T, add, mul> && abelian_group_c<T, add>);
template <class T, auto add, auto mul> concept semiring_c = !CHECK_ALGEBRA_ || (monoid_c<T, add> && monoid_c<T, mul> && properites_optt<T, add>::commutativity && properites_optt<T, mul>::nil && properites_optt_op2tt<T, add, mul>::distributivity);
template <class T, auto add, auto mul> concept ring_c = !CHECK_ALGEBRA_ || (rng_c<T, add, mul> && semiring_c<T, add, mul>);
template <class T, auto add, auto mul> concept commutative_ring_c = !CHECK_ALGEBRA_ || (ring_c<T, add, mul> && properites_optt<T, mul>::commutativity);
template <class T, auto add, auto mul> concept domain_c = !CHECK_ALGEBRA_ || (ring_c<T, add, mul> && properites_optt<T, mul>::non_zero_divisor);
template <class T, auto add, auto mul> concept integral_domain_c = !CHECK_ALGEBRA_ || (commutative_ring_c<T, add, mul> && domain_c<T, add, mul>);
template <class T, auto add, auto mul> concept division_ring_c = !CHECK_ALGEBRA_ || (ring_c<T, add, mul> && properites_optt<T, mul>::invertiblity);
template <class T, auto add, auto mul> concept field_c = !CHECK_ALGEBRA_ || (integral_domain_c<T, add, mul> && abelian_group_c<T, mul>);
// module-like
template <class T, class R, auto tadd, auto radd, auto rmul, auto mapping> concept Rmodule_c = !CHECK_ALGEBRA_ || (abelian_group_c<T, tadd> && ring_c<R, radd, rmul> && properites_optt_mp<T, R, tadd, mapping>::distributivity && properites_oprr_mp<T, R, radd, mapping>::associativity && properites_oprr_mp<T, R, rmul, mapping>::associativity && properites_mp<T, R, mapping>::identity);
template <class T, class R, auto tadd, auto radd, auto rmul, auto mapping> concept left_Rmodule_c = !CHECK_ALGEBRA_ || (Rmodule_c<T, R, tadd, radd, rmul, mapping> && left_mapping_c<T, R, mapping>);
template <class T, class R, auto tadd, auto radd, auto rmul, auto mapping> concept right_Rmodule_c = !CHECK_ALGEBRA_ || (Rmodule_c<T, R, tadd, radd, rmul, mapping> && right_mapping_c<T, R, mapping>);
template <class T, class R, auto tadd, auto radd, auto rmul, auto mapping> concept vector_space_c = !CHECK_ALGEBRA_ || (Rmodule_c<T, R, tadd, radd, rmul, mapping> && field_c<R, radd, rmul>);

}  // namespace tifa_libs
// clang-format on
#endif