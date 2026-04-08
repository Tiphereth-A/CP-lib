\begin{itemize}
    \item \(A\operatorname{adj}(A)=\operatorname{adj}(A)A=\operatorname{det}(A)I\)
    \item \(\operatorname{adj}(AB)=\operatorname{adj}(B)\operatorname{adj}(A)\)
    \item \(A\operatorname{adj}(A+B)B=B\operatorname{adj}(A+B)A\)
    \item \(\operatorname{adj}(A^T)=\operatorname{adj}(A)^T\)
    \item \(\operatorname{adj}(kA)=k^{n-1}\operatorname{adj}(A)\)
    \item \(\operatorname{det}(\operatorname{adj}(A))=\operatorname{det}(A)^{n-1}\)
    \item \(A^{-1}=\operatorname{det}(A)^{-1}\operatorname{adj}(A)\)
    \item 若 \(n\geq 2\), 则 \(\operatorname{adj}(\operatorname{adj}(A))=\operatorname{det}(A)^{n-2}A\)
    \item 若 \(A\) 是对称矩阵, 则 \(\operatorname{adj}(A)\) 也是对称矩阵
    \item 若 \(A\) 是反对称矩阵, 则 \((-1)^n\operatorname{adj}(A)\) 也是反对称矩阵
    \item 若 \(A\) 是 (半) 正定矩阵, 则 \(\operatorname{adj}(A)\) 也是 (半) 正定矩阵
    \item 若 \(A\), \(B\) 相似, 则 \(\operatorname{adj}(A)\), \(\operatorname{adj}(B)\) 也相似
    \item 若 \(n>2\), 则 \(A\neq 0\) 是正交矩阵当且仅当 \(\operatorname{adj}(A)=\pm A^T\)
    \item \(\operatorname{rk}(\operatorname{adj}(A))=\begin{cases}
              n, & \operatorname{rk}(A)=n,   \\
              1, & \operatorname{rk}(A)=n-1, \\
              0, & \text{otherwise}.
          \end{cases}\)
    \item 若 \(A\) 的特征值为 \(\lambda_1,\dots,\lambda_n\), 设 \(\prod_{i=1}^n\lambda_i=\lambda\), 则 \(\operatorname{adj}(A)\) 的特征值为 \(\lambda/\lambda_1,\dots,\lambda/\lambda_n\)
    \item 设 \(A\) 的特征多项式为 \(f(x)\), 则 \(\operatorname{adj}(A)=\dfrac{f(0)-f(A)}{A}=-\sum_{i=1}^n\left(\left[x^i\right]f(x)\right)A^{i-1}\)
\end{itemize}
