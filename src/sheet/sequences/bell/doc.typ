\[
    B_0 = 1,\, B_1 = 1,\, B_2 = 2,\, B_3 = 5
\]

\[
    B_4 = 15,\, B_5 = 52,\, B_6 = 203, \dots
\]

\[
    B_n = \sum_{k = 0} ^ n \stirlingII{n}{k}
\]

递推式:

\[
    B_{n + 1} = \sum_{k = 0} ^n \binom{n}{k} B_k
\]

EGF:

\[
    B(x) = \mathrm{e}^{\mathrm{e}^x - 1}
\]

Touchard 同余:

\[
    B_{n + p} \equiv (B_n + B_{n + 1}) \pmod p,~p\in\mathbb{P}
\]
