#include "../code/rand/gen.hpp"

tifa_libs::rand::Gen gen(std::mt19937(), std::uniform_int_distribution<int>(0, 114514));

// 随机数引擎
auto re = gen.rand_eng();

// 随机数分布
auto dist = gen.distrib();

// 获取下一个随机数
auto x = gen();
