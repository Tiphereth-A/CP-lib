#set page(
  paper: "a4",
  margin: (inside: 2cm, outside: 0.9cm, top: 1.7cm, bottom: 0.7cm),
  header: context {
    let headings = query(selector(heading).before(here()))
    if headings.len() > 0 {
      let h = headings.last()
      grid(
        columns: (1fr, 1fr, 1fr),
        align(left, h.body),
        align(center, counter(page).display()),
        [],
      )
    }
  },
)

#set text(
  font: ("Noto Sans", "Noto Sans CJK SC", "New Computer Modern"),
  size: 10pt,
)

#set raw(
  theme: "default",
)

#show raw: set text(font: ("Fira Code", "Noto Sans CJK SC", "DejaVu Sans Mono"), size: 9pt)

// Title page
#include "src/_titlepage/titlepage.typ"

#pagebreak()

// Table of contents
#columns(2)[
  #outline(
    depth: 3,
  )
]

#pagebreak()

// Colophon
#include "src/_colophon/colophon.typ"

#pagebreak()

// Main content
#counter(page).update(1)
#include ".cp-lib/src/doc.typ"
