#import "../../lib.typ": *

#let title = "abc482"

#import "e/main.typ": content as e

// 供大合集导入：作为一节（比赛标题 + 各题）
#let contest = () => [
  = #title
  #e()
]

// 单独编译本场比赛（单级目录）
#show: article
#contest()
