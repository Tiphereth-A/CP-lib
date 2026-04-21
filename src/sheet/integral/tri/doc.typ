\[
    \begin{aligned}
        \int \cos^m x \sin^n x \md x   = & \dfrac{1}{m+n} \cos^{m-1} x \sin^{n+1}x + \dfrac{m-1}{m+n}\int\cos^{m-2}x\sin^nx\md x       \\
        =                                & -\dfrac{1}{m+n} \cos^{m+1} x \sin^{n-1}x + \dfrac{n-1}{m+1} \int \cos^m x\sin^{n-2} x \md x
    \end{aligned}
\]

\[
    \int \dfrac{\md x}{a + b \sin x} = \begin{cases}
        \dfrac{2}{\sqrt{a^2-b^2}}\arctan\dfrac{a\tan\dfrac{x}{2}+b}{\sqrt{a^2-b^2}} + C                                                & (a^2 > b^2) \\
        \dfrac{1}{\sqrt{b^2-a^2}}\ln \left| \dfrac{a\tan\dfrac{x}{2}+b-\sqrt{b^2-a^2}}{a\tan\dfrac{x}{2}+b+\sqrt{b^2-a^2}} \right| + C & (a^2 < b^2)
    \end{cases}
\]

\[
    \int \dfrac{\md x}{a + b \cos x} = \begin{cases}
        \dfrac{2}{a+b}\sqrt\dfrac{a+b}{a-b} \arctan\left(\sqrt\dfrac{a-b}{a+b}\tan\dfrac{x}{2}\right) + C                                                 & (a^2 > b^2) \\
        \dfrac{1}{a+b}\sqrt\dfrac{a+b}{a-b} \ln \left| \dfrac{\tan\dfrac{x}{2}+\sqrt\dfrac{a+b}{b-a}}{\tan\dfrac{x}{2}-\sqrt\dfrac{a+b}{b-a}} \right| + C & (a^2 < b^2)
    \end{cases}
\]

\begin{multicols}{2}
    \(\displaystyle \int \dfrac{\md x}{a^2\cos^2x+b^2\sin^2x} = \dfrac{1}{ab} \arctan\left( \dfrac{b}{a}\tan x \right) + C\) \\
    \(\displaystyle \int \dfrac{\md x}{a^2\cos^2x-b^2\sin^2x} = \dfrac{1}{2ab}\ln\left|\dfrac{b\tan x+a}{b\tan x-a}\right| + C\)
\end{multicols}
