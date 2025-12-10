// Math operators matching LaTeX definitions
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

// Full reference function matching LaTeX \fullref
// Creates reference with number, name, and page number
#let fullref(label) = context {
  let target = query(label)
  if target.len() > 0 {
    let elem = target.first()
    let num = numbering(elem.numbering, ..counter(heading).at(elem.location()))
    let page-num = counter(page).at(elem.location()).first()
    [#num.#elem.body (#page-num 页)]
  } else {
    [???]
  }
}

// Path fix function matching LaTeX \fixpath
// Prepends ../ to paths for files in _gen/ directory
#let fixpath(path) = {
  "../" + path
}
