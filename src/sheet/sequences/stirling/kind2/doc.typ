\(n\brace k\) 表示 \(n\) 个元素划分成 \(k\) 个子集的方案数.

递推式:

\[
    \stirlingII{n}{k} = \stirlingII{n-1}{k-1} + k\stirlingII{n-1}{k}
\]

求一个: 容斥

\[
    \stirlingII{n}{k} = \frac{1}{k!} \sum_{i = 0}^k (-1)^i \binom{k}{i} (k - i)^n = \sum_{i = 0}^k \frac{(-1)^i}{i!} \frac{(k - i)^n}{(k - i)!}
\]

求同一行: FFT

求同一列: 指数生成函数

\[
    \sum_{n = 0}^\infty \stirlingII{n}{k} \frac{x^n}{n!} = \frac{\left(\mathrm{e}^x - 1\right)^k}{k!} = \frac{x^k}{k!} \left( \frac{\mathrm{e}^x - 1}{x} \right)^k
\]

普通生成函数

\[
    \sum_{n = 0}^\infty \stirlingII{n}{k} x^n = x^k \left(\prod_{i = 1}^k (1 - i x)\right)^{-1}
\]
