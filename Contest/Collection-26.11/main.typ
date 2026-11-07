#import "../../lib.typ": *

#let title = "Collection-26.11"

#import "a/main.typ": content as a

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #a()
]

// 单独编译本场比赛（单级目录，先输出目录）
#show: article
#outline(title: outline-title, depth: 2)
#contest()
