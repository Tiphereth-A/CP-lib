#include "add.dft.mtt.hpp"

_TEST(bs, f128);
_TEST(bd, f128);
_TEST(ms, f128);
_TEST(md, f128);
_TEST(ms64, f128);
_TEST(md64, f128);

BENCHMARK_MAIN();

/*comparison
CONV_same_length_md_f128 CONV_same_length_bd_f128 CONV_same_length_md64_f128
CONV_long_empty_md_f128 CONV_long_empty_bd_f128 CONV_long_empty_md64_f128
*/
