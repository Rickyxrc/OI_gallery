#import "../../../lib.typ": *

#let contest-id = "Collection-26.11"
#let problem-id = "a"
#let title = "[CF575A] Fibonotci"

#let statement = include problem-id + ".prob.typ"
#let solution = include problem-id + ".sol.typ"

#let content_ = title_ => make-problem(
  contest-id: contest-id,
  problem-id: problem-id,
  title: title_,
  statement: statement,
  solution: solution,
)
#let content = content_(upper(problem-id) + "." + title)

#show: article

#content_(contest-id + " " + upper(problem-id) + "." + title)()
