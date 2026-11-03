#import "../../lib.typ": *

#let title = "AAAsample"

#import "a/main.typ": content as a
#import "b/main.typ": content as b

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #a()
  #b()
]

// 单独编译本场比赛（单级目录）
#show: article
#outline(title: outline-title, depth: 2)
// #set document(title: title)
#contest()
