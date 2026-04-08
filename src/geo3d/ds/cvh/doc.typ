使用基于分治的 QuickHull 算法

\paragraph{时间复杂度} 平均 \(O(n\log n)\), 最差 \(O(nh)\), 其中 \(n\) 为点的总数, \(h\) 为凸包上的点数. 对于随机数据来说速度很快

\paragraph{空间复杂度} \(O(n)\)

\paragraph{参考文献} \cite{barber1996quickhull}

// {lib.hpp,start=3}
// {usage.cpp,start=2}
