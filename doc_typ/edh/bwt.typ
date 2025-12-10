
=== 构建方式

对给定的字符串 $s$, 列出所有循环平移后的结果, 按字典序排序后取所有串的最后一个字符

如对串 `banana$`, 列出所有循环平移后的结果:

```
$banana
a$banan
na$bana
ana$ban
nana$ba
anana$b
banana$
```

按字典序排序:

```
$banana
a$banan
ana$ban
anana$b
banana$
na$bana
nana$ba
```

取最后一位得到 `annb$aa`

和后缀数组对比:

```
i            : 0 1 2 3 4 5 6 7
s[i]         : $ b a n a n a $
sa[i]        :   7 6 4 2 1 5 3
s[sa[i] - 1] :   a n n b $ a a
bwt[i]       :   a n n b $ a a
```

不难发现其中的关系.

使用方式如下:

```cpp
bwt("#banana");     // -> "annb#aa"
bwt_inv("annb#aa"); // -> "#banana"
```

=== 注意

例子中的 `$` 为末尾标识符, 可换成任意字典序 *小于* 正文的字符, *不可省略*

使用时占位符放在正文最前端而不是末尾

=== 参考资料

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1214062423.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - Burrows-Wheeler transform]
)
