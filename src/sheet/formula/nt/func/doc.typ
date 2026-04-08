\begin{multicols}{3}
    \(\displaystyle \sum_{\delta\mid n}\varphi(\delta)d\left(\frac{n}{\delta}\right) = \sigma(n)\) \\
    \(\displaystyle \sum_{\delta\mid n}\left|\mu(\delta)\right| = 2^{\omega(n)}\) \\
    \(\displaystyle \sum_{\delta\mid n}2^{\omega(\delta)} = d(n^2)\) \\
    \(\displaystyle \sum_{\delta\mid n}d(\delta^2) = d^2(n)\) \\
    \(\displaystyle \sum_{\delta\mid n}d\left(\frac{n}{\delta}\right)2^{\omega(\delta)} = d^2(n)\) \\
    \(\displaystyle \sum_{\delta\mid n}\frac{\mu(\delta)}{\delta} = \frac{\varphi(n)}{n}\) \\
    \(\displaystyle \sum_{\delta\mid n}\frac{\mu(\delta)}{\varphi(\delta)} = d(n)\) \\
    \(\displaystyle \sum_{\delta\mid n}\frac{\mu^2(\delta)}{\varphi(\delta)} = \frac{n}{\varphi(n)}\)
\end{multicols}

\begin{equation}
    \sum_{i=1}^n\sum_{j=1}^m(i,j)^k=\sum_{D=1}^{\min\{n,m\}}\left\lfloor\frac{n}{D}\right\rfloor\left\lfloor\frac{m}{D}\right\rfloor\{\operatorname{id}_k*\mu\}(D)
\end{equation}

\begin{equation}
    \{\operatorname{id}_k*\mu\}(p^s)=p^{ks}-p^{k(s-1)}
\end{equation}

\begin{equation}
    \sum_{i = 1} ^ n \left[(i, n) = 1\right] i = n \frac {\varphi(n) + e(n)} 2
\end{equation}

\begin{equation}
    \sum_{i = 1} ^ n \sum_{j = 1} ^ i \left[(i, j) = d\right] = S_\varphi \left( \left\lfloor \frac n d \right\rfloor \right)
\end{equation}

\begin{equation}
    \sum_{i = 1} ^ n \sum_{j = 1} ^ m \left[(i, j) = d\right] = \sum_{d \mid  k} \mu\left( \frac k d \right) \left\lfloor \frac n k \right\rfloor \left\lfloor \frac m k \right\rfloor
\end{equation}

\begin{equation}
    \sum_{i = 1} ^ n f(i) \sum_{j = 1} ^ {\left\lfloor \frac n i \right\rfloor} g(j) = \sum_{i = 1} ^ n g(i) \sum_{j = 1} ^ {\left\lfloor \frac n i \right\rfloor} f(j)
\end{equation}

\begin{equation}
    \mu^2(n) = \sum_{d^2 \mid n} \mu (d)
\end{equation}

\begin{equation}
    \prod_{k=1,(k, m) = 1}^{m} k \equiv
    \begin{cases}
        -1 \pmod m, & m = 4, p^q, 2p^q \\
        1 \pmod m,  & \text{otherwise} \\
    \end{cases}
\end{equation}

\begin{equation}
    \sigma_k(n) = \sum_{d\mid n}d^k = \prod_{i=1}^{\omega(n)}\frac{p_i^{(a_i+1)k}-1}{p_i^k-1}
\end{equation}

\begin{eqnarray}
    &&J_k(n) = n^k\prod_{p\mid n}\left(1-\frac{1}{p^k}\right) \\
    &&\sum_{\delta\mid n}J_k(\delta) = n^k \\
    &&\sum_{\delta\mid n}\delta^sJ_r(\delta)J_s\left(\frac{n}{\delta}\right) = J_{r+s}(n)
\end{eqnarray}

其中 \(J_k(n)\) 是不大于 \(n\) 的正整数构成的 \(k\) 元组中, 与 \(n\) 构成互素 \((k + 1)\) 元组的个数

\begin{equation}
    \sum_{i=1}^{n} \sum_{j=1}^{n} [(i,j)=1]ij =  \sum_{i=1}^{n} i^2\varphi(i)
\end{equation}

\begin{equation}
    n\mid \varphi(a^n-1)
\end{equation}

\begin{equation}
    \sum_{\substack{1 \leq k \leq n,~(k, n) = 1}}f(\gcd(k-1, n)) = \varphi(n)\sum_{d\mid n}\frac{(\mu*f)(d)}{\varphi(d)}
\end{equation}

\begin{equation}
    \varphi([m, n])\varphi(\gcd(m,n)) = \varphi(m)\varphi(n)
\end{equation}

\begin{equation}
    \sum_{\delta\mid n}d^3(\delta) = \left(\sum_{\delta\mid n}d(\delta)\right)^2
\end{equation}

\begin{equation}
    d(uv) = \sum_{\delta\mid (u, v)}\mu(\delta)d\left(\frac{u}{\delta}\right)d\left(\frac{v}{\delta}\right)
\end{equation}

\begin{equation}
    \sigma_k(u)\sigma_k(v) = \sum_{\delta\mid (u, v)}\delta^k\sigma_k(\frac{uv}{\delta^2})
\end{equation}

\begin{equation}
    \mu(n) = \sum_{k=1}^n[(k, n)=1]\cos{2\pi \frac{k}{n}}
\end{equation}

\begin{equation}
    \varphi(n) = \sum_{k=1}^n[(k, n)=1] = \sum_{k=1}^n(k, n)\cos{2\pi \frac{k}{n}}
\end{equation}

\begin{equation}
    \begin{cases}
        S(n) = \sum_{k=1}^n(f * g)(k) \\
        \sum_{k=1}^nS(\lfloor \frac n k \rfloor) = \sum_{i=1}^nf(i)\sum_{j=1}^{\lfloor n/i \rfloor}(g * 1)(j)
    \end{cases}
\end{equation}

\begin{equation}
    \begin{cases}
        S(n) = \sum_{k=1}^n(f \cdot g)(k), g \text{ completely multiplicative} \\
        \sum_{k=1}^nS\left(\left\lfloor \frac n k \right\rfloor\right)g(k) = \sum_{k=1}^n(f * 1)(k)g(k)
    \end{cases}
\end{equation}
