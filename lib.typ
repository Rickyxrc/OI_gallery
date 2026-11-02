#import "style.typ": article, section
#import "config.typ": outline-title, show-solution, solution-title

#let code-block(content, lang: "cpp") = raw(content, lang: lang, block: true)

#let make-problem(
  contest-id: none,
  problem-id: none,
  title: none,
  statement: none,
  solution: none,
) = () => [
  == #title
  #statement

  #if show-solution [
    === #solution-title
    #solution
  ]
]
