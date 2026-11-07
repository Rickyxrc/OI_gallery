#import "../../lib.typ": *

#let title = "Codeforces Round 1132 (Div. 2)"

#import "a1/main.typ": content as a1
#import "a2/main.typ": content as a2
#import "b/main.typ": content as b
#import "c1/main.typ": content as c1
#import "c2/main.typ": content as c2

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #a1()
  #a2()
  #b()
  #c1()
  #c2()
]

// 单独编译本场比赛（单级目录，先输出目录）
#show: article
#outline(title: outline-title, depth: 2)
#contest()
