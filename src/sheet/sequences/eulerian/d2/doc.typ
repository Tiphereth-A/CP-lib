\(\eulerianII{n}{k}\): 每个数都出现两次的多重排列, 并且每个数两次出现之间的数都比它要大. 在此前提下有 \(k\) 个上升的方案数.

\[
    \eulerianII{n}{k} = (2n-k-1)\eulerianII{n-1}{k-1} + (k+1)\eulerianII{n-1}{k}
\]

\[
    \sum_{k = 0} ^ {n - 1} \eulerianII{n}{k} = (2n-1)!! = \frac{(2n)^{\underline n}} {2^n}
\]
