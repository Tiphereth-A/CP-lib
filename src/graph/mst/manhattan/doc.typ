给定 \(n\) 个点 \(p_i=(x_i,y_i)\), 点 \(i\) 和点 \(j\) 的边权为 \({\lVert p_i-p_j\rVert}_1=|x_i-x_j|+|y_i-y_j|\), 求该图的最小生成树

要想得到最终的最小生成树需对返回的边排序后应用 \fullref{ssec:graph-mst-kruskal}

\begin{minted}{cpp}
auto res = tifa_libs::manhattan_mst(vp);
std::ranges::sort(res);
auto mst = tifa_libs::kruskal(res, n);  
\end{minted}

\paragraph{复杂度} \(O(n\log n)\)

// {lib.hpp,start=3}
// {usage.cpp,start=2}
