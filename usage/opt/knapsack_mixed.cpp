#define PROBLEM "https://www.luogu.com.cn/problem/P1833"

#include "../../include/opt/knapsack_mixed.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 a0, b0, a1, b1, n;
  std::cin >> a0, std::cin.get(), std::cin >> b0 >> a1, std::cin.get(), std::cin >> b1 >> n;
  opt::knapsack_mixed<i32> kn(u32(i32(a1 - a0) * 60 + i32(b1 - b0)));
  for (u32 i = 0; i < n; ++i) {
    u32 t, p;
    i32 c;
    std::cin >> t >> c >> p;
    kn.add(t, c, p);
  }
  std::cout << kn.result().back() << '\n';
}

/*
爱与愁大神后院里种了 $n$ 棵樱花树, 每棵都有美学值 $C_i(0 \le C_i \le 200)$. 爱与愁大神在每天上学前都会来赏花. 爱与愁大神可是生物学霸, 他懂得如何欣赏樱花: 一种樱花树看一遍过, 一种樱花树最多看 $P_i(0 \le P_i \le 100)$ 遍, 一种樱花树可以看无数遍. 但是看每棵樱花树都有一定的时间 $T_i(0 \le T_i \le 100)$. 爱与愁大神离去上学的时间只剩下一小会儿了. 求解看哪几棵樱花树能使美学值最高且爱与愁大神能准时 (或提早) 去上学

## 输入格式
共 $n+1$行. 第 $1$ 行: 现在时间 $T_s$ (几时: 几分) , 去上学的时间 $T_e$ (几时: 几分), 爱与愁大神院子里有几棵樱花树 $n$. 这里的 $T_s$, $T_e$ 格式为: `hh:mm`, 其中 $0 \leq hh \leq 23$, $0 \leq mm \leq 59$, 且 $hh,mm,n$ 均为正整数. 第 $2$ 行到第 $n+1$ 行, 每行三个正整数: 看完第 $i$ 棵树的耗费时间 $T_i$, 第 $i$ 棵树的美学值 $C_i$, 看第 $i$ 棵树的次数 $P_i$ ($P_i=0$ 表示无数次, $P_i$ 是其他数字表示最多可看的次数 $P_i$)
$T_e-T_s \leq 1000$ (即开始时间距离结束时间不超过 $1000$ 分钟), $n \leq 10000$. 保证 $T_e,T_s$ 为同一天内的时间

## 输出格式
一个整数, 表示最大美学值

样例解释: 赏第一棵樱花树一次, 赏第三棵樱花树 $2$ 次
*/

/*
6:50 7:00 3
2 1 0
3 3 1
4 5 4
=============
11
*/