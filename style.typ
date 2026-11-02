// ============================================================
//  样式注入点：你所有的样式都写在这里。
//
//  重要：set / show 规则必须直接写在 article() 函数体内，
//        写在外层或嵌套函数里不会生效。
// ============================================================

#let article(body) = {
  set page(paper: "a4", margin: 2cm, numbering: "1")

  // 正文字体字号：拉丁字母/数学用 New Computer Modern，中文回退到霞鹜文楷 LXGW WenKai
  set text(size: 11pt, lang: "zh", font: ("New Computer Modern", "LXGW WenKai"))

  // 不显示标题编号，题号直接写在标题里（如 "A. 两数之和"）
  set heading(numbering: none)

  // ---- 自定义标题外观示例（可自行修改/删除）----
  // show heading: it => {
  //   set block(above: 1.4em, below: 0.7em)
  //   it
  // }

  // ---- 自定义代码块外观示例（可自行修改/删除）----
  // show raw.where(block: true): set block(
  //   fill: rgb("#f6f8fa"),
  //   inset: 10pt,
  //   radius: 4pt,
  // )

  import "@preview/codly:1.3.0": *
  import "@preview/codly-languages:0.1.1": *

  show: codly-init.with()

  show raw.line: set text(
    font: (
      (name: "Consolas", covers: "latin-in-cjk"),
      "LXGW WenKai", // 中文字体（请替换为你系统中已安装的中文字体名）
    ),
  )

  body
}

// 题面/题解内的小节标签：不是真正的标题，因此不进目录、不参与编号，
// 层级也永远正确。外观在这里定义，可自由调整。
#let section(label) = block(above: 1.1em, below: 0.4em, strong(label))
