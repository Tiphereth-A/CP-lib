#include "add.dft.mtt.hpp"

_TEST(bs, f64);
_TEST(bd, f64);
_TEST(ms, f64);
_TEST(md, f64);
_TEST(ms64, f64);
_TEST(md64, f64);

BENCHMARK_MAIN();

/*comparison
CONV_same_length_md_f64 CONV_same_length_bd_f64 CONV_same_length_md64_f64
CONV_long_empty_md_f64 CONV_long_empty_bd_f64 CONV_long_empty_md64_f64
*/
