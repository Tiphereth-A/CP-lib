// CP-lib Notebook - Typst Version
#set document(
  title: "CP-lib",
  author: ("Tifa", "tan60", "AgOH"),
)

#set page(
  paper: "a4",
  margin: (x: 1.5cm, y: 2cm),
  numbering: "1",
  columns: 1,
)

#set text(
  font: ("Noto Sans", "Noto Sans CJK SC"),
  size: 10pt,
  lang: "zh",
)

#set par(
  justify: true,
  leading: 0.65em,
)

#set heading(numbering: "1.")

// Configure code blocks with line numbers like LaTeX minted
#show raw.where(block: true): it => {
  set par(justify: false)
  set text(font: "Fira Code", size: 9pt)
  
  let lines = it.text.split("\n")
  let line-count = lines.len()
  
  block(
    stroke: 0.5pt + luma(200),
    inset: (left: 8pt, right: 8pt, top: 8pt, bottom: 8pt),
    radius: 0pt,
    width: 100%,
    fill: luma(252),
    {
      grid(
        columns: (auto, 1fr),
        column-gutter: 1em,
        row-gutter: 0.5em,
        ..lines.enumerate().map(((i, line)) => (
          align(right, text(fill: luma(120), str(i + 1))),
          align(left, raw(line, lang: it.lang))
        )).flatten()
      )
    }
  )
}

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

#raw(read("../src/main.cpp"), lang: "cpp")

#raw(read("../src/test.cpp"), lang: "cpp")

#raw(read("../src/.clang-format"), lang: "yaml")

#raw(read("../src/run.sh"), lang: "bash")

#pagebreak()

// Table of contents (two columns like LaTeX)
#set page(numbering: "1")
#counter(page).update(0)

#columns(2)[
  #outline(
    title: [目录],
    indent: auto,
  )
]

#pagebreak()

#counter(page).update(1)

// Include generated contents
#include "../_gen/contents_notebook.typ"
#include "../_gen/contents_cheatsheet.typ"

// Note: PDF embedding for cheat.pdf would need additional handling in Typst
// Typst doesn't have direct PDF embedding like LaTeX's \includepdf
// This could be handled separately or converted to images

// Bibliography section would also need separate handling in Typst
