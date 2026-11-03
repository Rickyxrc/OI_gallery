#import "../../lib.typ": *

#let title = "ICPC2026_Wuhan"

#import "d/main.typ": content as d
#import "g/main.typ": content as g
#import "j/main.typ": content as j
#import "k/main.typ": content as k

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #d()
  #g()
  #j()
  #k()
]

// 单独编译本场比赛（单级目录）
#show: article
#contest()
