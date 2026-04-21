\textbf{上升幂与普通幂的转换}

\[
    x^{\overline{n}}=\sum_{k} \stirlingI{n}{k} x^k
\]

\[
    x^n=\sum_{k} \stirlingII{n}{k} (-1)^{n-k} x^{\overline{k}}
\]

\textbf{下降幂与普通幂的转换}

\[
    x^n=\sum_{k} \stirlingII{n}{k} x^{\underline{k}} = \sum_{k} \binom{x}{k} \stirlingII{n}{k} k!
\]

\[
    x^{\underline{n}}=\sum_{k} \stirlingI{n}{k} (-1)^{n-k} x^k
\]

多项式的\textbf{点值}表示的每项除以阶乘之后卷上 \(\mathrm{e}^{-x}\) 乘上阶乘之后是牛顿插值表示, 不乘阶乘就是\textbf{下降幂}系数表示.

反过来的转换当然卷上 \(\mathrm{e}^x\) 就行了. 原理是每次差分等价于乘以 \((1 - x)\), 展开之后用一次卷积取代多次差分.

\subsubsection*{Stirling 多项式(Stirling 数关于斜线的性质)}

定义:

\[
    \sigma_n(x) = \frac{\stirlingI{x}{n}}{x(x-1)\dots(x-n)}
\]

\(\sigma_n(x)\) 的最高次数是 \(x^{n - 1}\). (所以作为唯一的特例, \(\sigma_0(x) = \dfrac{1}{x}\) 不是多项式.)

Stirling 多项式实际上非常神奇, 它与两类 Stirling 数都有关系.

\[
    \stirlingI{n}{n-k} = n^{\underline{k+1}} \sigma_k(n)
\]

\[
    \stirlingII{n}{n-k} = (-1)^{k+1} n^{\underline{k+1}} \sigma_k(-(n-k))
\]

不过它并不好求. 可以 \(O(k^2)\) 直接计算前几个点值然后插值, 或者如果要推式子的话可以用 \fullref{sssec:sheet-sequences-eulerian-d2}.
