// CP-lib Notebook - Typst Version
#set document(
  title: "CP-lib",
  author: ("Tifa", "tan60", "AgOH"),
)

// Page layout matching LaTeX geometry settings
// inner=2cm, outer=0.9cm, top=1.7cm, bottom=0.0cm
#set page(
  paper: "a4",
  margin: (left: 2cm, right: 0.9cm, top: 1.7cm, bottom: 0.7cm),
  numbering: "1",
  columns: 1,
  header: locate(loc => {
    let page-num = counter(page).at(loc).first()
    if page-num > 0 {
      set text(size: 9pt)
      grid(
        columns: (1fr, 1fr, 1fr),
        align: (left, center, right),
        [#context query(selector(heading).before(loc)).last().body],
        [#counter(page).display()],
        [#context query(selector(heading.where(level: 2)).before(loc)).last().body],
      )
      v(-0.5em)
      line(length: 100%, stroke: 0.5pt)
    }
  }),
  footer: locate(loc => {
    let page-num = counter(page).at(loc).first()
    if page-num > 0 {
      line(length: 100%, stroke: 0.5pt)
    }
  }),
)

#set text(
  font: ("Noto Sans", "Noto Sans CJK SC"),
  size: 10pt,
  lang: "zh",
)

#set par(
  justify: true,
  leading: 0.65em,
  first-line-indent: 0em,
)

// Heading spacing matching LaTeX titlesec settings
// titlespacing*{...}{0pt}{0.6ex}{0.6ex}
#set heading(numbering: "1.")
#show heading: it => {
  set block(above: 0.6em, below: 0.6em)
  it
}

// Configure code blocks matching LaTeX minted settings
// style=default, linenos, frame=single, framesep=0.8mm, 
// framerule=0.3pt, numbersep=0.8mm, baselinestretch=0.9, fontsize=\footnotesize
#show raw.where(block: true): it => {
  set par(justify: false, leading: 0.55em)  // baselinestretch=0.9
  set text(font: "Fira Code", size: 8pt)  // \footnotesize
  
  let lines = it.text.split("\n")
  let line-count = lines.len()
  
  block(
    stroke: 0.3pt + luma(200),  // framerule=0.3pt, frame=single
    inset: (left: 0.8mm, right: 0.8mm, top: 0.8mm, bottom: 0.8mm),  // framesep=0.8mm
    radius: 0pt,
    width: 100%,
    fill: luma(252),
    {
      grid(
        columns: (auto, 1fr),
        column-gutter: 0.8mm,  // numbersep=0.8mm
        row-gutter: 0em,
        ..lines.enumerate().map(((i, line)) => (
          align(right, text(fill: luma(120), size: 7pt, str(i + 1))),
          align(left, raw(line, lang: it.lang))
        )).flatten()
      )
    }
  )
}

// Math operators and commands matching LaTeX definitions
#let lcm = math.op("lcm")
#let argmin = math.op("arg min", limits: true)
#let argmax = math.op("arg max", limits: true)
#let sech = math.op("sech")
#let csch = math.op("csch")
#let arccot = math.op("arccot")
#let arcsec = math.op("arcsec")
#let arccsc = math.op("arccsc")
#let arcsinh = math.op("arcsinh")
#let arccosh = math.op("arccosh")
#let arctanh = math.op("arctanh")
#let arccoth = math.op("arccoth")
#let arcsech = math.op("arcsech")
#let arccsch = math.op("arccsch")

// Differential operator
#let dd = $upright(d)$

// Eulerian numbers: ⟨n k⟩
#let eulerian(n, k) = $angle.l #n #k angle.r$
#let eulerianII(n, k) = $angle.l angle.l #n #k angle.r angle.r$

// Stirling numbers: [n k] and {n k}
#let stirlingI(n, k) = $lr([#n #k])$
#let stirlingII(n, k) = $lr({#n #k})$

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

// Bibliography section
#pagebreak()
#bibliography("notebook.bib", title: "参考文献", style: "ieee")
