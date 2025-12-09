// CP-lib Notebook - Typst Version
#set document(
  title: "CP-lib",
  author: ("Tifa", "tan60", "AgOH"),
)

#set page(
  paper: "a4",
  margin: (x: 1.5cm, y: 2cm),
  numbering: "1",
)

#set text(
  font: "New Computer Modern",
  size: 10pt,
  lang: "zh",
)

#set par(
  justify: true,
  leading: 0.65em,
)

#set heading(numbering: "1.")

// Title page
#align(center)[
  #v(3cm)
  #image("../img/cplib-logo-ba-style.png", height: 6cm)
  
  #v(6cm)
  
  #text(size: 12pt)[
    #link("https://github.com/Tiphereth-A/CP-lib")
  ]
  
  #v(0.3cm)
  
  #link("https://github.com/Tiphereth-A")[Tifa], #link("https://github.com/hongmaoya")[tan60], #link("https://github.com/StableAgOH")[AgOH]
  
  (按首个修改本文档内容的 commit 时间顺序排列)
  
  #v(0.2cm)
  
  #datetime.today().display()
]

#pagebreak()

// Introduction
#set page(numbering: none)

本书代码默认数组下标从 $0$ 开始 ($[0, n)$), 故需注意题目下标是从 $0$ 开始 ($[0, n)$) 还是从 $1$ 开始 ($[1, n]$)

```cpp
#raw(read("../src/main.cpp"))
```

```cpp
#raw(read("../src/test.cpp"))
```

```yaml
#raw(read("../src/.clang-format"))
```

```bash
#raw(read("../src/run.sh"))
```

#pagebreak()

// Table of contents
#set page(numbering: "1")
#counter(page).update(0)

#outline(
  title: [目录],
  indent: auto,
)

#pagebreak()

#counter(page).update(1)

// Include generated contents
#include "../_gen/contents_notebook.typ"
#include "../_gen/contents_cheatsheet.typ"

// Note: PDF embedding for cheat.pdf would need additional handling in Typst
// Typst doesn't have direct PDF embedding like LaTeX's \includepdf
// This could be handled separately or converted to images

// Bibliography section would also need separate handling in Typst
