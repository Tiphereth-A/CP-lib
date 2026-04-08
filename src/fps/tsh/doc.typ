\paragraph{输入}~\\

\verb|f|: 多项式, \(\deg f=n\)

\verb|c|: 偏移量

\verb|fact|: 由 \fullref{ssec:comb-seq-fact} 生成的数组, 长度至少为 \(n+1\)

\verb|ifact|: 由 \fullref{ssec:comb-seq-ifact} 生成的数组, 长度至少为 \(n+1\)

\paragraph{输出}

多项式 \(g(x)=f(x+c)\)

// {lib.hpp,start=3}
// {usage.cpp,start=2}
