
建图

```cpp
u32 n;
std::string s;
std::cin >> n;
tifa_libs::str::ex_suffix_automaton sam;
flt_(u32, i, 0, n) {
  std::cin >> s;
  u32 last = 0;
  for (auto c : s)
  last = sam.extend(last, u32(c - 'a'));
}
```

代码对此无体现

多个字符串间的最长公共子串, 对每个状态建立一个集合 `pos`, 每次插入第 `i` 个串的一个字符后

`st.pos[last].push_back(i)`, 则对于每个状态 `u`

$
forall a, b in "st"[u]."pos" space "then" space "lcs"(a, b) space "is" space "str"(u)
$

$
forall a in "st"[u]."pos", b in "st"["st"[u]."link"]."pos" space "then" space "lcs"(a, b) space "in" space "str"(u, "st"[u]."link")
$

其中 `lcs(a,b)` 表示串 `a`, `b` 的最长公共子串, `str(u)` 表示状态 `u` 表示的串, `str(u, v)` 表示在后缀链接中 `u`, `v` 这条边的表示状态表示的串

然后按照 `len` 递减的顺序遍历, 通过后缀链接将当前状态的 `pos` 与其他状态的合并, 遍历所有的状态, 找到一个 `len` 最大且满足当前 `pos` 的 `size` 为 `n` 的状态的 `len` 即为解

两两之间的最长公共子串也可这么求

=== 复杂度

$O(|Sigma| log |Sigma|)$
