\begin{equation}
    \sum_{n\geq k}\frac{x^n}{n!}\stirlingI{n}{k}=\frac{\left(-\ln(1-x)\right)^k}{k!}
\end{equation}

\begin{equation}
    \sum_{n\geq k}\frac{x^n}{n!}\stirlingII{n}{k}=\frac{\left(\mathrm{e}^x-1\right)^k}{k!}
\end{equation}

\begin{equation}
    \sum_{n\geq k}x^n\stirlingII{n}{k}=\prod_{i=1}^k\frac{x}{1-\mathrm{i}x}
\end{equation}

\begin{equation}
    f_n=\sum_{k=0}^n\stirlingI{n}{k}g_k \iff g_n=\sum_{k=0}^n\stirlingII{n}{k}(-1)^{n-k}f_k
\end{equation}

\begin{equation}
    \stirlingI{n}{k}=\frac{n!}{k!}\frac{k}{n}\left[x^{n-k}\right]\left(\frac{x}{\mathrm{e}^x-1}\right)^n
\end{equation}

\begin{equation}
    \stirlingII{n}{k}=\frac{n!}{k!}\frac{k}{n}\left[x^{n-k}\right]\left(\frac{x}{\ln(1+x)}\right)^n
\end{equation}

注意: \eqref{cs:formula:s-right} 是对的, \fullref{sec:sheet-tcscs} 的第 43 个是错的

\begin{equation}
    \label{cs:formula:s-right}
    \stirlingI{n+m+1}{m}=\sum_{k=0}^m(n+k)\stirlingI{k+n}{k}
\end{equation}

\begin{equation}
    n^{\underline{n-m}}[n\geq m]=\sum_{k=0}^n\stirlingI{n+1}{k+1}\stirlingII{k}{m}(-1)^{m-k}
\end{equation}

\begin{equation}
    \stirlingII{-n+m}{-n}=\sum_k\binom{m-n}{m+k}\binom{m+n}{n+k}\stirlingI{-k}{-k-m}
\end{equation}
