\[
    B(x)=\sum_{i\ge 0}\frac{B_i x^i}{i!}=\frac x{\mathrm{e}^x-1}
\]

\[
    B_n=[n=0]-\sum_{i=0}^{n-1}\binom{n}{i}\frac{B_i}{n-k+1}
\]

\[
    \sum_{i=0}^n\binom{n+1}{i}B_i=0
\]

\[
    S_n(m)=\sum_{i=0}^{m-1}i^n=\sum_{i=0}^n\binom{n}{i}B_{n-i}\frac{m^{i+1}}{i+1}
\]

\[
    B_0 = 1, \, B_1 = -\frac{1}{2}, \, B_4 = -\frac{1}{30}, \, B_6 = \frac{1}{42}, \, B_8 = -\frac{1}{30}, \, \dots
\]

除了 \(B_1 = -\dfrac{1}{2}\) 以外, Bernoulli 数的奇数项都是 \(0\).

自然数幂次和关于次数的 EGF:

\[
    F(x)=\sum_{k=0}^\infty \frac{\sum_{i=0}^n i^k}{k!}x^k=\sum_{i=0}^n \mathrm{e}^{ix}=\frac{\mathrm{e}^{(n+1)x-1}}{\mathrm{e}^x-1}
\]
