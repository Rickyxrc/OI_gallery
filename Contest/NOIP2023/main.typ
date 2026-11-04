#import "../../lib.typ": *

#let title = "NOIP2023"

#import "b/main.typ": content as b
#import "c/main.typ": content as c
#import "d/main.typ": content as d

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #b()
  #c()
  #d()
]

// 单独编译本场比赛（单级目录）
#show: article
#outline(title: outline-title, depth: 2)
#contest()
