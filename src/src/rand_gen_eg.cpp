#include "../code/rand/gen.hpp"

int main() {
  // 初始化
  tifa_libs::rand::Gen<std::uniform_int_distribution<int>> gen;
  tifa_libs::rand::Gen<std::uniform_int_distribution<int>> gen2(0, 114514);
  // 设置范围
  gen.set_range(0, 114514);
  // 访问随机数生成器
  gen.rand_eng();
  // 访问随机数分布
  gen.distrib();
  // 输出下一个随机数
  std::cout << gen();
}
