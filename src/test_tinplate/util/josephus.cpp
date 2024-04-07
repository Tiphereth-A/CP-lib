#define PROBLEM "https://codeforces.com/gym/101955/problem/K"

#include "../../code/util/josephus.hpp"

int main() {
  u32 t_;
  std::cin >> t_;
  for (u32 kase = 1; kase <= t_; ++kase) {
    u64 n, m, k;
    std::cin >> n >> m >> k;
    std::cout << "Case #" << kase << ": " << tifa_libs::util::Josephus(n, k, m) + 1 << '\n';
  }
  return 0;
}

/*
Tonight $n$ young men are going to participate in Peter's campfire party. They decide to play an ancient counting-out game which was first described by Titus Flavius Josephus. Here is a brief introduction to the game.

Before starting the game, these young men will stand in a circle around the campfire and the first man to join the circle will start the game. Counting will begin at the first man and proceed around the circle in the counterclockwise direction repeatedly. That is, the first man will report one at the beginning, and the second one in the counterclockwise direction will report two, and so forth, until a poor man reports $k$ and consequently leaves the circle to become a bystander. The game will be repeated with the remaining men, restarting from the next man in the counterclockwise direction who will be the new first man, going in the same direction, until all the young men have left the circle.

Peter wanna be the $m$\-th one who left the circle since he strongly believes this number is lucky for him. As a sophisticated programmer, can you point out the right place he should stand at before the game start so that he can achieve his goal?

For the sake of clarity, we assume the index of the first man to join the circle is $1$, the index of the next man in his counterclockwise direction is $2$, and so on. By the definition, the index of the last man in that direction should be $n$, and your task is to determine the index of the place Peter wants.

**Input**

The input contains several test cases, and the first line contains a positive integer $T$ indicating the number of test cases which is up to $1000$.

For each test case, the only line contains three integers $n, m$ and $k$ where $1 \le n, m, k \le 10^{18}$ and $n \ge m$.

We guarantee that the sum of $\min\{m, k\}$ (i.e. the minimum of $m$ and $k$) in all test cases is no larger than $2 \times 10^6$.

**Output**

For each test case, output a line containing "Case #x: y" (without quotes), where x is the test case number starting from $1$, and y is the index of the right place.

**Note**

The sample cases indeed show the order of the young men to leave the circle when $(n, k)$ is set to $(10, 2)$ and $(10, 3)$ respectively.
*/

/*
20
10 1 2
10 2 2
10 3 2
10 4 2
10 5 2
10 6 2
10 7 2
10 8 2
10 9 2
10 10 2
10 1 3
10 2 3
10 3 3
10 4 3
10 5 3
10 6 3
10 7 3
10 8 3
10 9 3
10 10 3
===================
Case #1: 2
Case #2: 4
Case #3: 6
Case #4: 8
Case #5: 10
Case #6: 3
Case #7: 7
Case #8: 1
Case #9: 9
Case #10: 5
Case #11: 3
Case #12: 6
Case #13: 9
Case #14: 2
Case #15: 7
Case #16: 1
Case #17: 8
Case #18: 5
Case #19: 10
Case #20: 4
*/
