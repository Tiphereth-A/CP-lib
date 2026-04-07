本书代码默认数组下标从 $0$ 开始 ($[0, n)$), 故需注意题目下标是从 $0$ 开始 ($[0, n)$) 还是从 $1$ 开始 ($[1, n]$)

Path: `src/_colophon/main.cpp`

#raw(
  read("main.cpp").split("\n").slice(1).join("\n"),
  lang: "cpp",
  block: true,
)

Path: `src/_colophon/test.cpp`

#raw(
  read("test.cpp").split("\n").slice(1).join("\n"),
  lang: "cpp",
  block: true,
)

Path: `src/_colophon/.clang-format`

#raw(
  read(".clang-format"),
  lang: "yaml",
  block: true,
)

Path: `src/_colophon/run.sh`

#raw(
  read("run.sh"),
  lang: "bash",
  block: true,
)
